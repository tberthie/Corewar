/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:04:54 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/20 13:13:03 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

void			ft_printf(int fd, char *str, ...)
{
	va_list		lst;
	char		*tmp;

	va_start(lst, str);
	while (*str)
		if (*str == '%' && *(str + 1) == 's' && (str += 2))
		{
			tmp = va_arg(lst, char*);
			write(fd, tmp, ft_strlen(tmp));
		}
		else if (*str == '%' && *(str + 1) == 'd' && (str += 2))
		{
			tmp = ft_itoa(va_arg(lst, int));
			write(fd, tmp, ft_strlen(tmp));
			free(tmp);
		}
		else if (*str == '%' && *(str + 1) == 'p' && (str += 2))
		{
			tmp = ft_itoabase((int)va_arg(lst, void*), 16);
			write(fd, tmp, ft_strlen(tmp));
			free(tmp);
		}
		else
			write(fd, str++, 1);
}
