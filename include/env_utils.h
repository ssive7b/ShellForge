#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "../libft/include/libft.h"

typedef struct s_tty	t_tty;

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
char	*get_envp_value(char *key, t_list *env_list);
char	*find_exec_pathname(t_tty *tty, t_list *env_list, char *cmd_name);

# endif