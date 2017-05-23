/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:34:56 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 12:52:21 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include <stdarg.h>

void			d_parse(va_list ap, char *fmt, int fd)
{
	int			i;

	i = 0;
	if (fmt[0] == 's')
		ft_putstr_fd((const char *)va_arg(ap, char *), fd);
	else if (fmt[0] == 'c')
		ft_putchar_fd((char)va_arg(ap, int), fd);
	else if (fmt[0] == 'd')
		ft_putnbr_fd(va_arg(ap, int), fd);
	else if (fmt[0] == 'x')
		ft_putnbr_hex_fd(va_arg(ap, unsigned long int), fd);
	else if (fmt[0] == 'p')
	{
		ft_putstr_fd("0x", fd);
		ft_putnbr_hex_fd(va_arg(ap, unsigned long int), fd);
	}
}

void			ft_parsing(va_list ap, char *fmt, int fd)
{
	int			i;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] && fmt[i] == '%')
		{
			++i;
			d_parse(ap, fmt + i, fd);
		}
		else if (fmt[i] && fmt[i] != '\0' && fmt[i] != '%')
		{
			ft_putchar_fd(fmt[i], fd);
		}
		++i;
	}
}

void			ft_lprintf(int fd, char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	ft_parsing(ap, fmt, fd);
	va_end(ap);
}
