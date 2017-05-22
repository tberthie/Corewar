/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:51:13 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/24 17:41:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

#include <stdlib.h>

void	ft_strpush(char **str, char c)
{
	char			*n_str;
	unsigned int	len;

	n_str =
		((len = ft_strlen(*str)) % ALLOC_STR_CHAR) ?
		*str : (char*)ft_m(sizeof(char) * (len + ALLOC_STR_CHAR + 1));
	n_str[len] = c;
	n_str[len + 1] = '\0';
	if (n_str == *str)
		return ;
	while (len--)
		n_str[len] = (*str)[len];
	free(*str);
	*str = n_str;
}
