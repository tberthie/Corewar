/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strintabstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:13:45 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 13:13:49 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		ft_strintabstr(char **tab, char *str, size_t n)
{
	int i;

	i = 0;
	while (tab[i] && ft_strncmp(tab[i], str, n))
		++i;
	if (i == ft_ptrlen(tab))
		return (-1);
	return (i);
}
