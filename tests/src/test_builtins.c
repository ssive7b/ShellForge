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
	t_list	*env_list = create_env_list(env);

	(void)env_list;
	int fd_out = open("test_export.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	t_anode cmd_node = {
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
	unlink("test_export.txt"); // comment if needed to see the outputs
}

Test(builtins_suite, test_export_change_existing)
{
	char **env = __environ;
	t_list	*env_list = create_env_list(env);

	(void)env_list;
	int fd_out = open("test_export.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	t_anode cmd_node = {
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
	unlink("test_export.txt");
}

Test(builtins_suite, test_cd)
{
	char **env = __environ;
	t_list	*env_list = create_env_list(env);

	(void)env_list;
	t_anode cmd_node = {
		.type = NODE_COMMAND,
		.cmd_pathname = NULL,
		.args = (char *[]){"cd", NULL},
		.fd_in = STDIN_FILENO,
		.fd_out = STDOUT_FILENO
	};
	
    exec_builtin(&cmd_node);
	char *path = get_envp_value("PWD", *get_env());
    cr_assert(ft_strcmp(path, "/home/svet") == 0, "Failed to change pwd to home");

	cmd_node.args = (char *[]){"cd", "/home/svet/Documents", NULL};
	exec_builtin(&cmd_node);
	path = get_envp_value("PWD", *get_env());
	cr_assert(ft_strcmp(path, "/home/svet/Documents") == 0, "Failed to change to new pwd!");

	path = get_envp_value("OLDPWD", *get_env());
	cr_assert(ft_strcmp(path, "/home/svet") == 0, "Failed to change oldpwd!");
}