/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:45:54 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/16 16:45:55 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "types.h"
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

// string_utils.c
bool	safe_strjoin(char **dest, const char *source);
int		skip_whitesps(const char *str);
int		is_esc(const char *str, size_t idx);
int		find_char_qadj(const char *str, char char_to_find);
int		find_char(const char *str, char char_to_find);

// memory_utils.c
void	safe_free(void **ptr);
char	*safe_strdup(const char *str);

// error_handlers.c
void	ft_error_msg(const char *message);
void	shell_error(char *command, char *message);

// debug_utils.c
void	print_stack(t_stack *stack, const char *name);
void	print_ast(t_anode *node, int level);

// array_utils.c
void	free_2d_array(char ***array, int n);
int		count_args(char **args);
char	**allocate_args_array(int size);
bool	copy_args(char **dst, char **src, int count);

#endif
