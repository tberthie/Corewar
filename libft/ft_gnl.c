/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:48:31 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/24 17:41:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

char	*ft_gnl(int fd)
{
	char	*line;
	char	c;

	line = ft_strnew();
	while (read(fd, &c, 1) == 1 && c != '\n')
		ft_strpush(&line, c);
	if (c == '\n')
		return (line);
	free(line);
	return ((char*)0);
}
