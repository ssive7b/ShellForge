#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <fcntl.h>
#include "lexer.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "test.h"

Test(exec_tests, find_exec_pathname_should_find_correct_path)
{
    char *envp[] = {"PATH=/bin:/usr/bin", NULL};
    init_env(envp);
    t_list *env_list = *get_env();

    char *path = find_exec_pathname(NULL, env_list, "ls");
	printf("exec_pathname: <%s\n", path);
    cr_assert_not_null(path, "Executable path should not be NULL");
    cr_assert(access(path, F_OK) == 0, "Path should be a valid executable");
    free(path);
    char *invalid_path = find_exec_pathname(NULL, env_list, "nonexistent_command");
    cr_assert_null(invalid_path, "Nonexistent command should return NULL");
}