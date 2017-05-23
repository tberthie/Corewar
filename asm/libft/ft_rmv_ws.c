/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmv_ws.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:44:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/16 16:47:47 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char		*ft_rmv_ws(char *str)
{
	char	*s;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] <= ' ')
			++cnt;
		++i;
	}
	ft_m((void **)(&s), i - cnt);
	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] > ' ')
			s[cnt++] = str[i++];
		++i;
	}
	s[cnt] = '\0';
	return (s);
}
