/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:18:00 by gthomas           #+#    #+#             */
/*   Updated: 2017/04/24 15:27:34 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_putnbr_hex_fd(uintmax_t n, int fd)
{
	uintmax_t	nbr;

	nbr = n;
	if (nbr < 10)
		ft_putchar_fd(nbr + '0', fd);
	else if (nbr < 16 && nbr > 9)
		ft_putchar_fd(nbr - 10 + 'a', fd);
	else
	{
		ft_putnbr_hex_fd(nbr / 16, fd);
		if (nbr % 16 > 9)
			ft_putchar_fd((nbr % 16) - 10 + 'a', fd);
		else if (nbr % 16 < 10)
			ft_putchar_fd((nbr % 16) + '0', fd);
	}
}
