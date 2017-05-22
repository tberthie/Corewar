/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:48:47 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/26 13:23:14 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(unsigned int size)
{
	char	*mem;

	mem = (char*)ft_m(size);
	while (size--)
		mem[size] ^= mem[size];
	return ((void*)mem);
}
