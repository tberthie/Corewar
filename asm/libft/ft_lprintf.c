/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:34:56 by gthomas           #+#    #+#             */
/*   Updated: 2017/04/29 18:17:05 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include <stdarg.h>

int				parse_prec(char *fmt, int *i)
{
	int prec;

	prec = 0;
	if (fmt[*i] == '.' && ft_atoi(fmt + *i + 1) > 0)
	{
		prec = ft_atoi(fmt + *i + 1);
		*i += ft_intlen(ft_atoi(fmt + *i + 1));
	}
	return (prec);
}

void			d_parse(va_list ap, char *fmt, int prec, int fd)
{
	int i;

	i = 0;
	if (fmt[0] == 's')
		ft_putstr_fd((const char *)va_arg(ap, char *), fd);
	else if (fmt[0] == 'c')
	{
		while (i < prec - 1)
		{
			ft_putchar_fd('\0', fd);
			++i;
		}
		ft_putchar_fd((char)va_arg(ap, int), fd);
	}
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
	int i;
	int prec;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] && fmt[i] == '%')
		{
			++i;
			prec = parse_prec(fmt, &i);
			d_parse(ap, fmt + i, prec, fd);
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
