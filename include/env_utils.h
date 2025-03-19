#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "../libft/include/libft.h"

typedef struct	s_env
{
	char	*key;
	char	*value;
}	t_env;

// env_init.c
void	init_env(char **envp);
t_list	**get_env(void);

// env_utils.c
t_list	*to_env_node(char *env_string);

# endif