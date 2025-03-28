/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:19:39 by sstoev            #+#    #+#             */
/*   Updated: 2024/11/26 16:58:44 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printstr(int fd, const char *s)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}

int	ft_printptr(int fd, void *ptr)
{
	unsigned long long	address;
	int					printed_len;
	unsigned long long	temp;

	address = (unsigned long)ptr;
	printed_len = 0;
	if (!ptr)
		return (write(fd, "(nil)", 5));
	printed_len += write(fd, "0x", 2);
	if (address == 0)
		printed_len += write(fd, "0", 1);
	else
	{
		ft_puthex(fd, address, 'x');
		temp = address;
		while (temp > 0)
		{
			temp /= 16;
			printed_len++;
		}
	}
	return (printed_len);
}

int	ft_printhex(int fd, unsigned int num, const char format)
{
	int				printed_len;

	printed_len = 0;
	if (num == 0)
		printed_len += write(fd, "0", 1);
	else
	{
		ft_puthex(fd, num, format);
		printed_len = get_unbr_len(num, 16);
	}
	return (printed_len);
}

int	ft_printnbr(int fd, int num)
{
	char	*num_str;
	int		print_len;

	print_len = 0;
	num_str = ft_itoa(num);
	print_len = ft_printstr(fd, num_str);
	free(num_str);
	return (print_len);
}

int	ft_printnbr_unsigned(int fd, unsigned int unbr)
{
	int				printed_len;

	printed_len = 0;
	if (unbr == 0)
		printed_len += write(1, "0", 1);
	else
	{
		ft_putnbr_unsigned(fd, unbr);
		printed_len = get_unbr_len(unbr, 10);
	}
	return (printed_len);
}
