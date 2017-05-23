/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:48:43 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:48:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	*ft_m(unsigned int byte_nb)
{
	void	*ptr;

	if ((ptr = malloc((size_t)byte_nb)))
		return (ptr);
	exit(-1);
}
