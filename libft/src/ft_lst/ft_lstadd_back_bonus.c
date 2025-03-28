/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:42:33 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/30 15:22:47 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last_node = ft_lstlast(*lst);
		if (last_node)
			last_node->next = new;
	}
}

/*
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
	node2->next = NULL;
	printf("lstlast->content = %s\n", (char *)(ft_lstlast(node1)->content));
	ft_lstadd_back(&node1, node3);
	printf("lstlast->content = %s\n", (char *)(ft_lstlast(node1)->content));
	node1 = NULL;
	ft_lstadd_back(&node1, node3);
	printf("lstlast->content = %s\n", (char *)(ft_lstlast(node1)->content));
	return (0);
}
*/
