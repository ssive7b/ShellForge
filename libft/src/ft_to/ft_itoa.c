/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:16:51 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/25 21:06:34 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num_chars(int n);

char	*ft_itoa(int n)
{
	char			*string_number;
	size_t			num_chars;
	unsigned int	nbr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	num_chars = get_num_chars(n);
	string_number = (char *)malloc(sizeof(char) * (num_chars + 1));
	if (!string_number)
		return (NULL);
	string_number[num_chars--] = '\0';
	nbr = (unsigned int)n;
	if (n < 0)
	{
		string_number[0] = '-';
		nbr = (unsigned int)(-n);
	}
	while (nbr)
	{
		string_number[num_chars--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (string_number);
}

size_t	get_num_chars(int n)
{
	size_t			i;
	unsigned int	nbr;

	i = 0;
	if (n <= 0)
	{
		i++;
		nbr = (unsigned int)(-n);
	}
	else
		nbr = (unsigned int)n;
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	int	n;

	n = -2147483647;
	printf("num_chars: '%lu'\n", get_num_chars(n));
	printf("string_number: '%s'\n", ft_itoa(n));
	return (0);
}
*/