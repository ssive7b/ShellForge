#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "lexer.h"
#include "ast_mock.h"
#include "test.h"
#include "executioner.h"
#include "minishell.h"
#include "env_utils.h"
#include <stdio.h>

TestSuite(builtins_suite);

Test(builtins_suite, test_export_args)
{
	char **env = __environ;
	init_env(env);

	int fd_out = open("test_export_noargs.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = NULL,
		.args = (char *[]){"export", "USSS=main test", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = fd_out
	};
	
    exec_builtin(&cmd_node);
	t_env *new_entry_created = get_env_entry("USSS", *get_env());
    cr_assert(new_entry_created != NULL, "Failed to export new entry!");

	cmd_node.args = (char *[]){"export", NULL};
	exec_builtin(&cmd_node);
}

Test(builtins_suite, test_export_change_existing)
{
	char **env = __environ;
	init_env(env);

	int fd_out = open("test_export_noargs.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = NULL,
		.args = (char *[]){"export", "USSS=main test", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = fd_out
	};
	
    exec_builtin(&cmd_node);
	t_env *new_entry_created = get_env_entry("USSS", *get_env());
    cr_assert(ft_strcmp(new_entry_created->value, "main test") == 0, "Failed to export new entry!");

	cmd_node.args = (char *[]){"export", "USSS", NULL};
	exec_builtin(&cmd_node);
	cr_assert(ft_strcmp(new_entry_created->value, "main test") == 0, "Failed to export new entry!");

	cmd_node.args = (char *[]){"export", NULL};
	exec_builtin(&cmd_node);
}

Test(builtins_suite, test_cd)
{
	char **env = __environ;
	init_env(env);

	int fd_out = open("test_cd.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	t_ast_node cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = NULL,
		.args = (char *[]){"cd", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = fd_out
	};
	
    exec_builtin(&cmd_node);
	char *path = get_envp_value("PWD", *get_env());
	printf("pwd: %s\n", path);
    cr_assert(ft_strcmp(path, "/home/svet") == 0, "Failed to change pwd to home");

	cmd_node.args = (char *[]){"cd", "/home/svet/Documents", NULL};
	exec_builtin(&cmd_node);
	path = get_envp_value("PWD", *get_env());
	printf("pwd: %s\n", path);
	cr_assert(ft_strcmp(path, "/home/svet/Documents") == 0, "Failed to change to new pwd!");

	path = get_envp_value("OLDPWD", *get_env());
	printf("oldpwd: %s\n", path);
	cr_assert(ft_strcmp(path, "/home/svet") == 0, "Failed to oldpwd!");
}