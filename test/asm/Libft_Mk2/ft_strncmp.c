/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:51:02 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:51:03 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	while (*s1 == *s2 && --n)
	{
		++s1;
		++s2;
	}
	return (*s1 != *s2);
}
