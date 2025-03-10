/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:54:33 by cschnath          #+#    #+#             */
/*   Updated: 2025/03/06 22:55:49 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INIT_TOKENS 10
# define GROWTH 5

# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_cmd
{
	// **commands
	// Input / output files
	// Arguments
	// Operators
	// Number of pipes
}		t_cmd;

// Tokenize.c
char	**resize_tokens(char **tokens, int *capacity, int count);
char	*create_token(const char *start, int len);
int		skip_spaces(const char *input, int i);
int		process_quotes(const char *input, int *i, char **tokens, int *count,
			int *capacity);
int		process_word(const char *input, int *i, char **tokens, int *count,
			int *capacity);
char	**tokenize(const char *input, int *token_count);
void	free_tokens(char **tokens);
void	print_tokens(char **tokens);
int		make_tokens(char *input);

// Init.c
void	ft_init(int argc, char **argv);

#endif
