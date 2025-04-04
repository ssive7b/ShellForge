#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include "types.h"
# include "../libft/include/libft.h"

typedef struct	s_shell
{
	char				*cwd;
	char				*prompt;
	char				*line;
	struct s_list		*env_list;
	struct s_ast_node	*ast_tree;
	int					exit_status;
	char				**envp;
}	t_shell;

// inits.c
void	*init_minishell(t_shell *minish, char **envp);

#endif