/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:15:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/22 14:38:55 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*get_file(int *j, char *str, char *tmp, char *buf)
{
	int		i;
	int		fd;
	int		ret;

	i = 0;
	chmod(str, 0666);
	if ((fd = open(str, O_RDONLY)) == -1)
	{
		ft_lprintf(2, "Error in openning %s file", str);
		exit(EXIT_FAILURE);
	}
	while ((ret = read(fd, buf, 4095)))
	{
		ft_realloc(&tmp, ret);
		while (i < ret)
		{
			tmp[*j] = buf[i];
			++i;
			*j += 1;
		}
		i = 0;
	}
	close(fd);
	return (tmp);
}

void		parse(t_asm *vasm, char *str)
{
	char	*tmp;
	char	buf[4096];
	int		j;

	init_asm(vasm);
	if (!(tmp = malloc(1)))
		exit(EXIT_FAILURE);
	tmp[0] = '\0';
	if (!(vasm->file_name = (char *)malloc(ft_strlen(str))))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->file_name, str, ft_strlen(str) - 3);
	vasm->file_name = ft_strcat(vasm->file_name, "s");
	tmp = get_file(&j, str, tmp, buf);
	init_cmd(vasm);
	print_hex(vasm, tmp, j);
	if (tmp)
		free(tmp);
}

int			main(int ac, char **av)
{
	t_asm	vasm;

	if (ac == 2 && av[1])
	{
		if (ft_stristr(av[1], ".cor") == -1)
			return (-1);
		parse(&vasm, av[1]);
	}
	return (0);
}
