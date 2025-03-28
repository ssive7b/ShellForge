/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:53:39 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/26 10:55:50 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
static char	ft_test(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return ('S');
}

int	main(void)
{
	char const	*s;

	s = "ipsum libro pak";
	printf("strmapi: '%s'\n", ft_strmapi(s, &ft_test));
	return (0);
}
*/