#include "lexer.h"

char	*handle_quotes(t_lexer *lx, char quote_type)
{
	size_t	start_idx;
	char	*quoted_str;

	lx->idx++; // Skip opening quote
	start_idx = lx->idx;
	while (lx->input[lx->idx] && lx->input[lx->idx] != quote_type)
		lx->idx++;
	// Error: Unclosed quote
	if (lx->input[lx->idx] != quote_type)
	{
		printf("Syntax error: unclosed %c quote\n", quote_type);
		return (NULL);
	}
	// Extract quoted content (without quotes)
	quoted_str = ft_substr(lx->input, start_idx, lx->idx - start_idx);
	lx->idx++; // Skip closing quote
	return (quoted_str);
}
