#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <fcntl.h>
#include "lexer.h"
#include "ast_mock.h"
#include "test.h"
#include "executioner.h"
#include "minishell.h"

TestSuite(execution_suite);

Test(execution_suite, test_redirection_output)
{
	t_tty		sh;
	t_ast_node	node;
    t_redirection redir = {.type = REDIR_OUTPUT, .file_name = "output.txt"};  // ">"
    
	node.type = NODE_COMMAND;
	node.args = (char *[]){"ls", NULL};
	node.cmd_pathname = "/bin/ls";
	node.redir = &redir;
	
	handle_redirections(&redir);

    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);

    printf("Hello Test\n");
    close(fd);

    FILE *fp = fopen("output.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    cr_assert_str_eq(buffer, "Hello Test\n", "Output redirection failed!");
}

Test(execution_suite, test_pipe_execution)
{
    t_ast_node *cmd1 = malloc(sizeof(t_ast_node));
    cmd1->type = NODE_COMMAND;
    cmd1->cmd_name = strdup("echo");
    cmd1->args = (char *[]){"echo", "main test", NULL};

    t_ast_node *cmd2 = malloc(sizeof(t_ast_node));
    cmd2->type = NODE_COMMAND;
    cmd2->cmd_name = strdup("grep");
    cmd2->args = (char *[]){"grep", "main", NULL};

    t_ast_node *pipe_node = malloc(sizeof(t_ast_node));
    pipe_node->type = NODE_PIPE;
    pipe_node->left = cmd1;
    pipe_node->right = cmd2;

    int stdout_backup = dup(STDOUT_FILENO);
    int pipe_fd[2];
    pipe(pipe_fd);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);

    execute_ast(pipe_node);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100];
    read(pipe_fd[0], buffer, sizeof(buffer));
    close(pipe_fd[0]);

    cr_assert(strstr(buffer, "main") != NULL, "Pipe execution failed!");
}

Test(execution_suite, test_command_execution)
{
    t_ast_node cmd_name = { .type = NODE_COMMAND, .cmd_name = "echo", .args = (char *[]){"echo", "Hello", NULL} };
    
    int stdout_backup = dup(STDOUT_FILENO);
    int fd[2];
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    execute_ast(&cmd_name);

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);

    char buffer[100];
    read(fd[0], buffer, sizeof(buffer));
    close(fd[0]);

    cr_assert_str_eq(buffer, "Hello\n", "Command execution failed!");
}