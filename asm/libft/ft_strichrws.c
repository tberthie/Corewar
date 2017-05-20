/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strichrws.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:20:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/16 16:21:09 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int			ft_strichrws(const char *s)
{
	char	*src;
	int		i;

	src = (char *)s;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] <= ' ')
			return (i);
		i++;
	}
	return (-1);
}
