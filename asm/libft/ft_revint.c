/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:35:03 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:36:43 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

unsigned int		ft_revint(unsigned int nb)
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
