/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:48:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/17 14:50:46 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memcpy(void *dest, const void *src, unsigned int byte_nb)
{
	unsigned int	i;

	i = 0;
	while (i != byte_nb)
	{
		((char*)dest)[i] = ((const char*)src)[i];
		++i;
	}
}
