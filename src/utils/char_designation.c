/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_designation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:59:02 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/14 00:59:03 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_designation.h"

int	ft_is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

int	ft_is_operator(char c)
{
	if (ft_strchr("><|&()", c))
		return (1);
	return (0);
}

int	ft_check_form_op(char prev, char current)
{
	if ((prev == '<' && current == '<')
		|| (prev == '>' && current == '>')
		|| (prev == '|' && current == '|')
		|| (prev == '&' && current == '&'))
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

int	ft_is_meta_char(const char c)
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

int	ft_is_unquoted_char(const char c)
{
	return (!ft_is_meta_char(c)
			&& !ft_is_quote(c)
			&& !ft_is_whitespace(c)
			&& c != '\0');
}

int	ft_is_expansion(char c)
{
	return (c == '$' || c == '`');
}
