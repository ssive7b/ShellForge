/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:17:45 by sstoev            #+#    #+#             */
/*   Updated: 2024/11/26 17:00:20 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	handle_specifier(int fd, va_list args, const char format);

int	ft_printf(char const *input_str, ...)
{
	va_list	args;
	size_t	input_len;

	input_len = 0;
	va_start(args, input_str);
	while (*input_str)
	{
		if (*input_str == '%')
		{
			input_str++;
			input_len += handle_specifier(1, args, *input_str);
		}
		else
			input_len += write(1, input_str, 1);
		input_str++;
	}
	va_end(args);
	return (input_len);
}

int	ft_dprintf(int fd, char const *input_str, ...)
{
	va_list	args;
	size_t	input_len;

	input_len = 0;
	va_start(args, input_str);
	while (*input_str)
	{
		if (*input_str == '%')
		{
			input_str++;
			input_len += handle_specifier(fd, args, *input_str);
		}
		else
			input_len += write(fd, input_str, 1);
		input_str++;
	}
	va_end(args);
	return (input_len);
}

static int	handle_specifier(int fd, va_list args, const char format)
{
	size_t	input_len;

	input_len = 0;
	if (format == 'c')
		input_len += ft_printchar(fd, va_arg(args, int));
	else if (format == 's')
		input_len += ft_printstr(fd, va_arg(args, char *));
	else if (format == 'p')
		input_len += ft_printptr(fd, va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		input_len += ft_printnbr(fd, va_arg(args, int));
	else if (format == 'u')
		input_len += ft_printnbr_unsigned(fd, va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		input_len += ft_printhex(fd, va_arg(args, unsigned int), format);
	else if (format == '%')
		input_len += ft_printpercent(fd);
	return (input_len);
}
