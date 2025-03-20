#ifndef EXECUTIONER_H
# define EXECUTIONER_H

# include "minishell.h"

// builtins
// pwd
t_list	**get_cwd(void);
void	ft_exec_pwd(t_list *env_list);

#endif