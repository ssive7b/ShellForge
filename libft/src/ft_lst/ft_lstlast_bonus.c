/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:30:03 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/30 15:24:33 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
	node2->next = node3;
	node3->next = NULL;
	printf("lstlast->content = %s\n", (char *)(ft_lstlast(node1)->content));
	return (0);
}
*/
