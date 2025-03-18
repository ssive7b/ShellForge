#ifndef TEST_H
# define TEST_H

# include "lexer.h"
# include "ast_mock.h"

// test_lexer_utils.c
char	*ft_get_token_alias(t_token *token);
t_token	*ft_check_lexer_output(char *const input, char *const expected_res);

#endif