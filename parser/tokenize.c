/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:35:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/03/06 23:04:36 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft.h"

// Resizes the token array if needed
char	**resize_tokens(char **tokens, int *capacity, int count)
{
	if (count < *capacity)
		return (tokens);
	*capacity += GROWTH;
	return (realloc(tokens, *capacity * sizeof(char *))); // Make realloc function
}

// Creates a new token from the string
char	*create_token(const char *start, int len)
{
	return (strndup(start, len)); // Make strndup function
}

// Skips over spaces in the input string
int	skip_spaces(const char *input, int i)
{
	while (isspace(input[i])) // Make isspace function
		i++;
	return (i);
}

// Processes quoted tokens (single or double quotes)
int	process_quotes(const char *input, int *i, char **tokens, int *count,
		int *capacity)
{
	char	quote;
	int		start;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (1);
	(*i)++;
	tokens = resize_tokens(tokens, capacity, *count);
	tokens[(*count)++] = create_token(&input[start], *i - start - 1);
	return (0);
}

// Processes unquoted tokens
int	process_word(const char *input, int *i, char **tokens, int *count,
		int *capacity)
{
	int	start;

	start = *i;
	while (input[*i] && !isspace(input[*i]) && input[*i] != '\''
		&& input[*i] != '"')
		(*i)++;
	tokens = resize_tokens(tokens, capacity, *count);
	tokens[(*count)++] = create_token(&input[start], *i - start);
	return (0);
}

// Tokenizes the input string (under 20 lines)
char	**tokenize(const char *input, int *token_count)
{
	int		i;
	int		capacity;
	int		count;
	char	**tokens;

	i = 0;
	capacity = INIT_TOKENS;
	count = 0;
	tokens = malloc(capacity * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '"') {
			if (process_quotes(input, &i, tokens, &count, &capacity))
				return (NULL); }
		else if (process_word(input, &i, tokens, &count, &capacity))
			return (NULL);
	}
	tokens[count] = NULL;
	*token_count = count;
	return (tokens);
}

// Frees the allocated memory for tokens
void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

// Prints all the tokens
void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		printf("Token: [%s]\n", tokens[i++]);
}

// Main function for testing the tokenizer
int	make_tokens(char *input)
{
	int		token_count;
	char	**tokens;

	tokens = tokenize(input, &token_count);
	if (!tokens)
	{
    	printf("Error: Unclosed quote detected\n");
        exit (1);
    }
	else
	{
		print_tokens(tokens);
		free_tokens(tokens);
	}
	return (0);
}
