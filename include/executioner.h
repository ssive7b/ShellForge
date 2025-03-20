#ifndef EXECUTIONER_H
# define EXECUTIONER_H

# include "../libft/include/libft.h"

typedef struct s_tty		t_tty;
typedef struct s_ast_node	t_ast_node;

// function pointer for exec mode
typedef void	*(*t_exec_mode)(t_tty *sh, t_ast_node);

// builtins
// pwd
char	**get_cwd(void);
void	ft_exec_pwd(t_list *env_list);

#endif