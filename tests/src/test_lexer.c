#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "lexer.h"

#define SEPARATOR "\n------------------------------------------\n"

Test(lexer_tests, test_ft_lexer_empty_input)
{
    char input[] = "";
    t_token *result = ft_lexer(input);
	cr_log_info(SEPARATOR);
    cr_log_info("Testing empty input\n");
    cr_assert_null(result, "Expected %s for empty input, but got non-NULL", input);
}

Test(lexer_tests, test_ft_lexer_single_token)
{
    char input[] = "token";
    t_token *result = ft_lexer(input);
	cr_log_info(SEPARATOR);
    cr_log_info("Testing single token input: '%s'\n", input);
    cr_assert_not_null(result, "Expected non-NULL for single token input, but got NULL");
    cr_assert_eq(result->type, TOKEN_WORD, "Expected token type TOKEN_WORD, but got %d", result->type);
    cr_assert_str_eq(result->value, input, "Expected token value %s, but got '%s'", input, result->value);
    cr_assert_null(result->next, "Expected NULL next token, but got non-NULL");
}

Test(lexer_tests, test_ft_lexer_multiple_tokens)
{
    char input[] = "token1 token2";
    t_token *result = ft_lexer(input);
	cr_log_info(SEPARATOR);
    cr_log_info("Testing multiple tokens input: '%s'\n", input);
    cr_assert_not_null(result, "Expected non-NULL for multiple tokens input, but got NULL");
    cr_assert_eq(result->type, TOKEN_WORD, "Expected first token type TOKEN_WORD, but got %d", result->type);
    cr_assert_str_eq(result->value, "token1", "Expected first token value 'token1', but got '%s'", result->value);
    cr_assert_not_null(result->next, "Expected non-NULL next token, but got NULL");
    cr_assert_eq(result->next->type, TOKEN_WORD, "Expected second token type TOKEN_WORD, but got %d", result->next->type);
    cr_assert_str_eq(result->next->value, "token2", "Expected second token value 'token2', but got '%s'");
    cr_assert_null(result->next->next, "Expected NULL next token after second token, but got non-NULL");
}