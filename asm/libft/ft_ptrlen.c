/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:35:07 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/29 12:56:07 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		ft_ptrlen(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		++i;
	return (i);
}
