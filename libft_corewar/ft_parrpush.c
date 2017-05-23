/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:49:27 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/17 18:04:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

#include <stdlib.h>

void	ft_parrpush(void ***tab, void *elem)
{
	void			**n_tab;
	unsigned int	arr_len;

	arr_len = ft_parrlen(*tab);
	n_tab = (arr_len % ALLOC_PARR) ? *tab :
	(void**)ft_m(sizeof(void*) * (arr_len + ALLOC_PARR + 1));
	n_tab[arr_len] = elem;
	n_tab[arr_len + 1] = (void*)0;
	if (n_tab == *tab)
		return ;
	while (arr_len--)
		n_tab[arr_len] = (*tab)[arr_len];
	free(*tab);
	*tab = n_tab;
}
