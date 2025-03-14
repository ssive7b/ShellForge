#include <criterion/criterion.h>
#include <string.h>
#include "minishell.h"
#include "lexer.h"


char	*ft_get_token_alias(t_token *token)
{
	if (!token)
		return (NULL);
	switch (token->type)
	{
		case TOKEN_WORD_UNQUOTED:
			return ("UW");
		case TOKEN_WORD_SQUOTED:
			return ("SW");
		case TOKEN_WORD_DQUOTED:
			return ("DW");
		case TOKEN_DELIMITER:
			return ("D");
		case TOKEN_PIPE:
			return ("P");
		case TOKEN_REDIR_APPEND:
			return ("R_APP");
		case TOKEN_REDIR_HEREDOC:
			return ("R_HD");
		case TOKEN_REDIR_IN:
			return ("R_IN");
		case TOKEN_REDIR_OUT:
			return ("R_OUT");
		default:
			return ("UNK");
	}
}

t_token	*ft_check_lexer_output(char *const input, char *const expected_res)
{
	size_t	idx = 0;
	size_t	len = 0;
	t_token	*head = ft_lexer(input);
	t_token *current_token;
	char	*token_alias;
	int		cmp_res;

	if (expected_res == NULL)
	{
		cr_assert_null(head, "Tokens was expected to be NULL.\n\ninput: %s\nlexer_output: %s\nexpected_output: %s\n", input, head, expected_res);
		return (NULL);
	}
	current_token = head;
	len = strlen(expected_res);
	while (current_token && idx < len)
	{
		token_alias = ft_get_token_alias(current_token);
		cmp_res = strncmp(token_alias, expected_res + idx, strlen(token_alias));
		cr_assert_eq(cmp_res, 0, "Incorrect tokenization detected.\n\ninput: %s\nlexer_output: %s\nexpected_output: %s\n", input, head, expected_res);
		current_token = current_token->next;
		idx += strlen(token_alias) + 1;
	}
	if (current_token)
		cr_assert_null(current_token, "Tokens checked are valid, but extra tokens detected.\n\ninput: %s\nlexer_output: %s\nexpected_output: %s\n", input, head, expected_res);
	cr_assert_eq(idx >= len, 1, "Tokens checked are valid, but some missing tokens detected.\n\ninput: %s\nlexer_output: %s\nexpected_output: %s\n", input, head, expected_res);
	return (head);
}
