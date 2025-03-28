#ifndef TEST_H
# define TEST_H

typedef struct s_token	t_token;

// test_lexer_utils.c
char	*ft_get_token_alias(t_token *token);
t_token	*ft_check_lexer_output(char *const input, char *const expected_res);

#endif