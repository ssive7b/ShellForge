/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:30:58 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/30 15:23:29 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next_node = (*lst)->next;
		del((*lst)->content);
		(*lst)->content = NULL;
		free(*lst);
		*lst = next_node;
	}
	*lst = NULL;
}
/*
void	del_nod(void *contents)
{
	free(contents);
}

int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	char	*str1 = ft_strdup("happy");
	char	*str2 = ft_strdup("happy new");
	char	*str3 = ft_strdup("brum");

	node1 = ft_lstnew(str1);
	node2 = ft_lstnew(str2);
	node3 = ft_lstnew(str3);
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	ft_lstclear(&node1, del_nod);
	return (0);
}
*/
