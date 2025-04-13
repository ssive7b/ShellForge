/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:37:38 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 00:09:22 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_elements(char **arr, size_t i);

void	ft_bubble_sort(char **arr, size_t size)
{
	int		swapped;
	size_t	i;

	if (size < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				swap_elements(arr, i);
				swapped = 1;
			}
			i++;
		}
		size--;
	}
}

static void	swap_elements(char **arr, size_t i)
{
	char	*temp;

	temp = arr[i];
	arr[i] = arr[i + 1];
	arr[i + 1] = temp;
}
