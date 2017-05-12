/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 15:52:36 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 12:47:54 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include "./includes/get_next_line.h"

char		*get_file(int fd, char *buf, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (get_next_line(fd, &buf))
	{
		ft_realloc(&tmp, (int)ft_strlen(buf) + 1);
		++j;
		while (buf[i])
			tmp[j++] = buf[i++];
		tmp[j] = '\n';
		if (buf)
			free(buf);
		i = 0;
	}
	tmp[j] = '\0';
	if (buf)
		free(buf);
	return (tmp);
}

char		*ft_parse(char *file_name)
{
	char	*buf;
	char	*tmp;
	int		fd;

	buf = NULL;
	tmp = NULL;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);
	tmp = get_file(fd, buf, tmp);
	close(fd);
	return (tmp);
}
