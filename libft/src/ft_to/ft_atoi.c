/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:30:46 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/23 20:39:07 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		if (result * sign > 2147483647)
			return (2147483647);
		else if (result * sign < -2147483648)
			return (-2147483648);
		nptr++;
	}
	return ((int)(result * sign));
}
/*
int main(int argc, char **argv)
{
 	if (argc != 2)
		return (0);
	printf("atoi = '%d'\n", atoi(argv[1]));
	printf("ft_atoi = '%d'\n", ft_atoi(argv[1]));
    return (0);
}
*/