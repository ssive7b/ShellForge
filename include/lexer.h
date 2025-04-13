/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:40:24 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 22:01:25 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/include/libft.h"
# include "types.h"
# include <stdbool.h>

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	size_t			idx;
	t_token			*tokens;
	int				error;
}					t_lexer;

// function pointers for state transitioning
typedef void		*(*t_lexer_state)(t_lexer *lexer);

// lexer.c
t_lexer				*run_tokenizer(const char *input);
void				handle_single_quote(t_token token, t_lexer *lx);
t_lexer_state		word_state(t_lexer *lx);
t_lexer_state		operator_state(t_lexer *lx);
t_lexer_state		delimiter_state(t_lexer *lx);
t_token_type		get_op_token_type2(const char *input);
t_token_type		get_op_token_type(const char *input);

// lexer_utils.c
t_lexer				*init_tokenizer(const char *input);
t_token				*ft_create_token(t_token token_data);
void				ft_append_token(t_token **tokens_queue, t_token *new_token);
void				ft_print_tokens(t_token *tokens);

// lexer_cleaners.c
void				cleanup_lexer(t_lexer **lexer);
void				free_tokens(t_token *tokens);

#endif
