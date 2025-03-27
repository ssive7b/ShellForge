/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:24:39 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/20 12:24:41 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"

char	**get_cwd(void)
{
	static char	*cwd = NULL;

	return (&cwd);
}

void	exec_pwd(t_ast_node *node)
{
	char	*buffer;
	size_t	size_buffer;

	(void)node;
	size_buffer = PATH_MAX + 1;
	buffer = malloc(sizeof(char) * size_buffer);
	if (!buffer)
		return ;
	getcwd(buffer, size_buffer);
	printf("%s\n", buffer);
	*get_cwd() = buffer;
	// free buffer???
}
