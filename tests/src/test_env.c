#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <fcntl.h>
#include "lexer.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "test.h"

TestSuite(environment_suite);

Test(environment_suite, init_env_should_populate_list)
{
    char *envp[] = {
        "USER=student",
        "PATH=/bin:/usr/bin",
        "HOME=/home/student",
        NULL
    };

	t_list	*env_list = create_env_list(envp);

    cr_assert_not_null(env_list, "Environment list should not be NULL");

    t_env *env_entry = env_list->content;
    cr_assert_str_eq(env_entry->key, "USER", "First environment variable key should be USER");
    cr_assert_str_eq(env_entry->value, "student", "First environment variable value should be student");

    env_list = env_list->next;
    cr_assert_str_eq(((t_env *)env_list->content)->key, "PATH", "Second key should be PATH");
}

Test(environment_suite, find_exec_pathname_should_find_correct_path)
{
    char *envp[] = {"PATH=/bin:/usr/bin", NULL};
    t_list	*env_list = create_env_list(envp);

    char *path = find_cmd_path(env_list, "ls");
    cr_assert_not_null(path, "Executable path should not be NULL");
    cr_assert(access(path, F_OK) == 0, "Path should be a valid executable");
    free(path);
    char *invalid_path = find_cmd_path(env_list, "nonexistent_command");
    cr_assert_null(invalid_path, "Nonexistent command should return NULL");
}

Test(environment_suite, to_env_node_should_create_valid_node)
{
    t_list *node = to_env_node("EDITOR=vim");
    
    cr_assert_not_null(node, "Node should not be NULL");
    t_env *env_entry = node->content;

    cr_assert_str_eq(env_entry->key, "EDITOR", "Key should be 'EDITOR'");
    cr_assert_str_eq(env_entry->value, "vim", "Value should be 'vim'");
}

Test(environment_suite, get_envp_value_should_return_correct_value)
{
    char *envp[] = {
        "USER=student",
        "SHELL=/bin/bash",
        "LANG=en_US.UTF-8",
        NULL
    };

    t_list	*env_list = create_env_list(envp);

    cr_assert_str_eq(get_envp_value("USER", env_list), "student", "USER should return 'student'");
    cr_assert_str_eq(get_envp_value("SHELL", env_list), "/bin/bash", "SHELL should return '/bin/bash'");
    cr_assert_str_eq(get_envp_value("LANG", env_list), "en_US.UTF-8", "LANG should return 'en_US.UTF-8'");
    cr_assert_null(get_envp_value("INVALID", env_list), "Invalid key should return NULL");
}
