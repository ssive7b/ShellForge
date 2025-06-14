/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_mock.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:42:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/27 07:29:31 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_MOCK_H
# define AST_MOCK_H

# include <stdbool.h>
# include "types.h"
# include "../libft/include/libft.h"

typedef struct s_redirection
{
	t_redir_type			type;
	char					*file_name;
	char					*delimiter_heredoc;
	int						fd;
	int						open_flags;
}							t_redir;

typedef struct s_ast_node
{
	t_ntype					type;
	char					*cmd_pathname;
	char					**args;
	int						pid;
	int						fd_in;
	int						fd_out;
	int						exit_status;
	t_list					*redirs;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
}							t_anode;

typedef struct s_ast_stack
{
	t_anode					*node;
	struct s_ast_stack		*next;
}							t_stack;

#endif
