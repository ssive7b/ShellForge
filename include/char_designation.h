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

int		is_whitespace(char c);
int		check_form_op(char prev, char current);
int		is_quote(char c);
int		is_meta_char(const char c);
int		is_unq_char(const char c);

#endif
