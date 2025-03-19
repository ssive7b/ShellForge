#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include "../libft/include/libft.h"
# include "ast_mock.h"
# include "env_utils.h"

typedef struct	s_tty
{
	char		cwd[PATH_MAX];
	char		*prompt;
	char		*line;
	t_env		*env_list;
	t_ast_node	*ast_tree;
	int			exit_status;
}	t_tty;

#endif