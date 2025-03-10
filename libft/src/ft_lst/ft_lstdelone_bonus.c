/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:27:16 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/30 15:23:48 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	lst->content = NULL;
	free(lst);
}
/*
void	del_nod(void *contents)
{
	free(contents);
}

int	main(void)
{
	t_list	*node1;
	char	*str1 = ft_strdup("happy");

	node1 = ft_lstnew(str1);
	assert (node1 != NULL);
	ft_lstdelone(node1, del_nod);
	printf("Node one freed successfully\n");
	return (0);
}
*/
