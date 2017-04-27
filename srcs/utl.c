/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:14:05 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/27 16:52:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			error(char *file, char *msg)
{
	if (file)
	{
		ft_printf(2, "corewar: %s\n", file);
		ft_printf(2, RED"%s\n"EOC, msg);
	}
	else
	{
		ft_printf(2, "corewar: execution error\n", file);
		ft_printf(2, RED"%s\n"EOC, msg);
	}
	exit(1);
}

void			hex_dump(unsigned char hex)
{
	ft_putchar(hex < 16 ? '0' : ("0123456789ABCDEF")[hex % 16]);
	hex = hex >= 16 ? hex / 16 : hex;
	ft_putchar(("0123456789ABCDEF")[hex % 16]);
}

unsigned int	rev_int(unsigned int nb)
{
	unsigned int	new;
	unsigned int	bytes;

	new = 0;
	bytes = 4;
	while (bytes)
	{
		bytes--;
		new |= ((nb >> 8 * bytes) & 0xff) << (8 * (3 - bytes));
	}
	return (new);
}
