#ifndef CHAR_DESIGNATION_H
# define CHAR_DESIGNATION_H

# include <stdbool.h>

# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''
# define PIPE '|'

int		ft_is_whitespace(char c);
int		ft_is_operator(char c);
int		ft_check_form_op(char prev, char current);
int		ft_is_quote(char c);
int		ft_is_meta_char(const char c);
int		ft_is_unquoted_char(const char c);

#endif