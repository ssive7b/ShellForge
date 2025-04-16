/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_designation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:50:33 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/16 15:50:34 by sstoev           ###   ########.fr       */
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
