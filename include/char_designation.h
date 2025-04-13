/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_designation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:07:19 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/13 00:07:22 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_DESIGNATION_H
# define CHAR_DESIGNATION_H

# include <stdbool.h>
# include "types.h"
# include "../libft/include/libft.h"

int		ft_is_whitespace(char c);
int		ft_is_operator(char c);
int		ft_check_form_op(char prev, char current);
int		ft_is_quote(char c);
int		ft_is_meta_char(const char c);
int		ft_is_unquoted_char(const char c);

#endif