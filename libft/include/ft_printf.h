/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:43:34 by sstoev            #+#    #+#             */
/*   Updated: 2024/10/27 18:28:02 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// ft_printf.c
int		ft_printf(char const *input_str, ...);

// ft_dprintf.c
int		ft_dprintf(int fd, char const *input_str, ...);

// ft_printf_utils.c
int		ft_printstr(int fd, const char *s);
int		ft_printptr(int fd, void *ptr);
int		ft_printhex(int fd, unsigned int num, const char format);
int		ft_printnbr(int fd, int num);
int		ft_printnbr_unsigned(int fd, unsigned int unbr);

// auxiliary_funcs.c
int		ft_printchar(int fd, int c);
void	ft_puthex(int fd, unsigned long long num, const char format);
int		get_unbr_len(unsigned long unbr, int base);
void	ft_putnbr_unsigned(int fd, unsigned int unbr);
int		ft_printpercent(int fd);

#endif
