/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:55:48 by sstoev            #+#    #+#             */
/*   Updated: 2024/11/26 16:56:40 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printchar(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

int	get_unbr_len(unsigned long unbr, int base)
{
	int	unbr_len;

	unbr_len = 0;
	while (unbr > 0)
	{
		unbr /= base;
		unbr_len++;
	}
	return (unbr_len);
}

void	ft_puthex(int fd, unsigned long long num, const char format)
{
	char	digit;

	if (num >= 16)
		ft_puthex(fd, num / 16, format);
	digit = "0123456789abcdef"[num % 16];
	if (format == 'X' && digit >= 'a' && digit <= 'f')
		digit -= 32;
	write(fd, &digit, 1);
}

void	ft_putnbr_unsigned(int fd, unsigned int unbr)
{
	char	digit;

	if (unbr >= 10)
		ft_putnbr_unsigned(fd, unbr / 10);
	digit = (unbr % 10) + '0';
	write(fd, &digit, 1);
}

int	ft_printpercent(int fd)
{
	return (write(fd, "%", 1));
}
