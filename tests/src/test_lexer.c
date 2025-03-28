#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "lexer.h"
#include "test.h"


TestSuite(lexer_suite);

Test(lexer_suite, empty_input_test)
{
    ft_check_lexer_output("", NULL);
	ft_check_lexer_output("''", "SW");
	ft_check_lexer_output("\"\"", "DW");
	ft_check_lexer_output("\"\"''", "DW SW");
}

Test(lexer_suite, simple_pipe)
{
	ft_check_lexer_output("echo \"a\" | cat", "UW D DW D P D UW");
}