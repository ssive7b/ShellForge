#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "types.h"
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

// string_utils.c
bool	safe_strjoin(char **dest, const char *source);
char	*ft_strjoin_multiple(char **str_list, size_t num_strings);
int		ft_skip_whitespaces(const char *str);
int		ft_is_escaped(const char *str, size_t idx);
int		ft_find_char_qadjusted(const char *str, char char_to_find);
int		ft_find_char(const char *str, char char_to_find);

// memory_utils.c
void	safe_free(void **ptr);
char	*safe_strdup(const char *str);

// error_handlers.c
void	ft_error_msg(const char *message);

// debug_utils.c
void	print_stack(t_ast_stack *stack, const char *name);
void	print_ast(t_ast_node *node, int level);

// array_utils.c
void	ft_free_2d_array(char ***array, int n);
int		count_args(char **args);
char	**allocate_args_array(int size);
bool	copy_args(char **dst, char **src, int count);

#endif