/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 23:32:20 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/28 23:34:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_memset(void *mem, unsigned int size, char c)
{
	char	*tmp;

	tmp = mem;
	while (size--)
		tmp[size] = c;
}
