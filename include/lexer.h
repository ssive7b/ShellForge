/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:40:24 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/28 23:16:04 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "../libft/include/libft.h"
# include "types.h"

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char			*input;
	size_t			idx;	
	t_token			*tokens;
	t_token			*head;
	int				error;
}	t_lexer;

// function pointers for state transitioning
typedef void	*(*t_lexer_state)(t_lexer *lexer);

// lexer.c
t_lexer	*run_tokenizer(const char *input);

// lexer_utils.c
t_lexer	*init_tokenizer(const char *input);
t_token	*clone_token(t_token token_data);
bool	add_token_to_lex(t_lexer *lex, t_token *new_token);
void	print_tokens(t_token *tokens);
size_t	extract_word_token(t_lexer *lx, t_token *token, size_t start);

// lexer_cleaners.c
void	cleanup_lexer(t_lexer **lexer);
void	free_tokens(t_token *tokens);

#endif
