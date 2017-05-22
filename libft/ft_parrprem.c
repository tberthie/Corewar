/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrprem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:49:24 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/20 13:20:39 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	ft_parrprem(void **tab, void *elem)
{
	unsigned int	arr_len;

	arr_len = ft_parrlen(tab);
	while (*tab != elem)
	{
		++tab;
		--arr_len;
	}
	while (--arr_len)
	{
		tab[0] = tab[1];
		++tab;
	}
	tab[0] = 0;
}
