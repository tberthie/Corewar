/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:50:51 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:50:53 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

#include <stdlib.h>

void	ft_strins(char **str, char c, unsigned int i)
{
	char			*n_str;
	unsigned int	len;

	n_str =
	((len = ft_strlen(*str)) % ALLOC_STR_CHAR) ?
	*str : (char*)ft_m(sizeof(char) * (len + ALLOC_STR_CHAR + 1));
	++len;
	n_str[len] = '\0';
	while (--len != i)
		n_str[len] = (*str)[len - 1];
	n_str[len] = c;
	if (n_str == *str)
		return ;
	while (i--)
		n_str[i] = (*str)[i];
	free(*str);
	*str = n_str;
}
