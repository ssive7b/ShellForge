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

# include <stdio.h>
# include "../libft/include/libft.h"
# include "types.h"

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct	s_lexer
{
	char			*input;
	size_t			idx;
	int				line_number;	// for error reporting
	int				column_number;	// for error reporting			
	t_token			*tokens;
	int				error;			// error state
}	t_lexer;

// function pointers for state transitioning
typedef void	*(*t_lexer_state)(t_lexer *lexer);

// lexer.c
t_token	*ft_lexer(char *input);

// lexer_utils.c
void	ft_init_lex(t_lexer *lx, char *input);
t_token	*ft_create_token(t_token token_data);
void	ft_append_token(t_token **tokens_queue, t_token *new_token);
void	ft_print_tokens(t_token *tokens);

#endif
