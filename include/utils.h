#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>

// string_utils.c
char	*ft_strjoin_multiple(char **str_list, size_t num_strings);
int		ft_skip_whitespaces(const char *str);
int		ft_is_escaped(const char *str, size_t idx);
int		ft_find_char_idx(const char *str, char char_to_find);

// memory_utils.c
void	ft_free_2d_array(char **array, int n);

#endif