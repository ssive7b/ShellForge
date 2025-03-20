#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include "../libft/include/libft.h"

typedef struct	s_tty
{
	char				*cwd;
	char				*prompt;
	char				*line;
	struct s_list		*env_list;
	struct s_ast_node	*ast_tree;
	int					exit_status;
}	t_tty;

#endif