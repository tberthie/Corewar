/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:05:59 by gthomas           #+#    #+#             */
/*   Updated: 2017/03/08 13:41:33 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void		ft_realloc(char **str, const int buffer)
{
	int		str_size;
	int		i;
	char	*tmp;

	i = 0;
	str_size = ft_strlen((*str));
	if (!(tmp = (char *)malloc((str_size + 1) * sizeof(char))))
		return ;
	while (i < str_size)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = '\0';
	free((*str));
	(*str) = (char *)malloc((buffer + str_size + 1) * sizeof(char));
	i = 0;
	while (i < str_size)
	{
		(*str)[i] = tmp[i];
		i++;
	}
	(*str)[i] = '\0';
	free(tmp);
	tmp = NULL;
}
