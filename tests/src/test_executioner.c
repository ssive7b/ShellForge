#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "lexer.h"
#include "ast_mock.h"
#include "test.h"
#include "executioner.h"
#include "minishell.h"

TestSuite(execution_suite);

// Mock function to simulate execution
static void	mock_exec_astree(t_shell *sh, t_ast_node *node)
{
    if (node->type == NODE_COMMAND)
        execute_command(sh, node);
    else if (node->type == NODE_PIPE)
        execute_pipe(sh, node);
    else if (node->type == NODE_REDIRECTION)
        execute_redirection(sh, node);
    else if (node->type == NODE_AND)
        execute_and(sh, node);
    else if (node->type == NODE_OR)
        execute_or(sh, node);
}

Test(execution_suite, test_command_execution)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;

	t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/echo",
		.args = (char *[]){"echo", "main test", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    int stdout_backup = dup(STDOUT_FILENO);
    int fd[2];

    if (pipe(fd) == -1)
		printf("pipe_error\n");

	cmd_node.fd_in = fd[0];
	cmd_node.fd_out = fd[1];
	
    mock_exec_astree(sh, &cmd_node);

	close(fd[1]);
	waitpid(cmd_node.pid, NULL, 0);
	
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100] = {0};
    read(fd[0], buffer, sizeof(buffer) - 1);
	close(fd[0]);
    cr_assert_str_eq(buffer, "main test\n", "Command execution failed!");
	free(sh);
}

Test(execution_suite, test_pipe_execution)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;

	t_ast_node cmd1 = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/ls",
		.args = (char *[]){"ls", NULL, NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

	t_ast_node cmd2 = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/grep",
		.args = (char *[]){"grep", "Make", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

	t_ast_node pipe_node = {
		.type = NODE_PIPE,
		.left = &cmd1,
		.right = &cmd2
	};

    int stdout_backup = dup(STDOUT_FILENO);
    int pipe_fd[2];
    pipe(pipe_fd);

    cmd1.fd_out = pipe_fd[1];  // Left command writes to pipe
    cmd2.fd_in = pipe_fd[0];   // Right command reads from pipe

    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);

    execute_pipe(sh, &pipe_node); // Execute pipe logic

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100] = {0};
    read(pipe_fd[0], buffer, sizeof(buffer) - 1);
    close(pipe_fd[0]);

    cr_assert(strstr(buffer, "Makefile") != NULL, "Pipe execution failed!");
	free(sh);
}


Test(execution_suite, test_redirection_output)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;
	
    t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/echo",
		.args = (char *[]){"echo", "Hello" , "How", "Are", "You", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_redir redir = {
		.type = REDIR_OUTPUT,
		.file_name = "output.txt"
	};

    t_ast_node redir_node = {
		.type = NODE_REDIRECTION,
		.redir = &redir,
		.left = &cmd_node
	};

    mock_exec_astree(sh, &redir_node);

    FILE *fp = fopen("output.txt", "r");
    char buffer[100] = {0};
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    cr_assert_str_eq(buffer, "Hello How Are You\n", "Output redirection failed!");
	unlink("output.txt");
	free(sh);
}


Test(execution_suite, test_redirection_input)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;

    FILE *fp = fopen("input.txt", "w");
    fputs("Hello Input Test\n", fp);
    fclose(fp);

    t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/cat",
		.args = (char *[]){"cat", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_redir redir = {
		.type = REDIR_INPUT,
		.file_name = "input.txt"
	};

    t_ast_node redir_node = {
		.type = NODE_REDIRECTION,
		.redir = &redir,
		.left = &cmd_node
	};

    int stdout_backup = dup(STDOUT_FILENO);
    int fd[2];
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    mock_exec_astree(sh, &redir_node);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100] = {0};
    read(fd[0], buffer, sizeof(buffer));
    close(fd[0]);
    cr_assert_str_eq(buffer, "Hello Input Test\n", "Input redirection failed!");
	unlink("input.txt");
	free(sh);
}

Test(execution_suite, test_redirection_append)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;

    FILE *fp = fopen("output_append.txt", "w");
    fclose(fp);

    t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/echo",
		.args = (char *[]){"echo", "Appended Text", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_redir redir = {
		.type = REDIR_APPEND,
		.file_name = "output_append.txt"
	};

    t_ast_node redir_node = {
		.type = NODE_REDIRECTION,
		.redir = &redir,
		.left = &cmd_node
	};

    mock_exec_astree(sh, &redir_node);

    FILE *fp_read = fopen("output_append.txt", "r");
    char buffer[100] = {0};
    fgets(buffer, sizeof(buffer), fp_read);
    fclose(fp_read);

    cr_assert_str_eq(buffer, "Appended Text\n", "Append redirection failed!");
	unlink("output_append.txt");
	free(sh);
}

Test(execution_suite, test_and_execution)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;

    t_ast_node cmd_fail = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/false",
		.args = (char *[]){"false", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_ast_node cmd_echo = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/echo",
		.args = (char *[]){"echo", "Success", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_ast_node and_node = {
		.type = NODE_AND,
		.left = &cmd_fail,
		.right = &cmd_echo
	};

    int stdout_backup = dup(STDOUT_FILENO);
    int fd[2];
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    mock_exec_astree(sh, &and_node);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100] = {0};
    read(fd[0], buffer, sizeof(buffer));
    close(fd[0]);

    cr_assert(buffer[0] == '\0', "AND execution failed!");
	free(sh);
}

Test(execution_suite, test_or_execution)
{
	t_shell *sh = malloc(sizeof(t_shell));
	sh->envp = NULL;

    t_ast_node cmd_fail = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/false",
		.args = (char *[]){"false", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_ast_node cmd_echo = {
		.type = NODE_COMMAND,
		.cmd_pathname = "/bin/echo",
		.args = (char *[]){"echo", "Success", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};

    t_ast_node or_node = {
		.type = NODE_OR,
		.left = &cmd_fail,
		.right = &cmd_echo
	};

    int stdout_backup = dup(STDOUT_FILENO);
    int fd[2];
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    mock_exec_astree(sh, &or_node);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100] = {0};
    read(fd[0], buffer, sizeof(buffer));
    close(fd[0]);

    cr_assert_str_eq(buffer, "Success\n", "OR execution failed!");
	free(sh);
}

Test(execution_suite, test_heredoc)
{
    t_shell *sh = malloc(sizeof(t_shell));
    sh->envp = NULL;

    int stdin_backup = dup(STDIN_FILENO);
    int pipefd[2];
    pipe(pipefd);
    write(pipefd[1], "heredoc test\nEOF\n", 17);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    t_ast_node cmd_node = {
        .type = NODE_COMMAND,
        .cmd_pathname = "/bin/cat",
        .args = (char *[]){"cat", NULL},
        .fd_in = STDIN_FILENO,
        .fd_out = STDOUT_FILENO
    };

    t_redir redir = {
        .type = REDIR_HEREDOC,
        .delimiter_heredoc = "EOF"
    };

    t_ast_node redir_node = {
        .type = NODE_REDIRECTION,
        .redir = &redir,
        .left = &cmd_node
    };

    int stdout_backup = dup(STDOUT_FILENO);
    int fd[2];
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    mock_exec_astree(sh, &redir_node);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
    dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);

    char buffer[100] = {0};
    read(fd[0], buffer, sizeof(buffer));
	char *buffer_ = ft_substr(buffer, 21, 100);
    close(fd[0]);
	printf("heredoc buffer: %s\n", buffer_);
    cr_assert_str_eq(buffer_, "heredoc test\n", "Heredoc handling failed!");
    free(sh);
}