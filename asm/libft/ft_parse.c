/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 15:52:36 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 11:15:33 by gthomas          ###   ########.fr       */
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
		++j;
		ft_realloc(&tmp, (int)ft_strlen(buf) + 1);
		while (buf[i])
			tmp[j++] = buf[i++];
		tmp[j] = '\n';
		if (buf)
			free(buf);
		i = 0;
	}
	if (j >= 0)
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
