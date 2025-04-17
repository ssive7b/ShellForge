/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_designation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:59:02 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/27 10:50:18 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_designation.h"

int	is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

int	check_form_op(char prev, char current)
{
	if ((prev == '<' && current == '<')
		|| (prev == '>' && current == '>')
		|| (prev == '|' && current == '|')
		|| (prev == '&' && current == '&'))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

int	is_meta_char(const char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '|'
		|| c == '&'
		|| c == ';'
		|| c == '('
		|| c == ')'
		|| c == ','
		|| c == '<'
		|| c == '>');
}

int	is_unq_char(const char c)
{
	return (!is_meta_char(c)
		&& !is_quote(c)
		&& !is_whitespace(c)
		&& c != '\0');
}
