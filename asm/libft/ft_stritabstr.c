/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stritabstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:30:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/04/25 13:35:57 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		ft_stritabstr(char **tab, char *str, size_t n)
{
	int i;

	i = 0;
	while (tab[i] && ft_strncmp(tab[i], str, n))
		++i;
	if (i == ft_ptrlen(tab))
		return (-1);
	return (i);
}
