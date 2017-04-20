/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:57:55 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/20 16:13:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#include "libft.h"

#include <fcntl.h>
#include <unistd.h>

static char		check_champion(char *path, void *buffer)
{
	header_t	*header;

	header = (header_t*)buffer;
	if ((reverse_bytes((int)header->magic) != COREWAR_EXEC_MAGIC))
	{
		ft_printf(2, "corewar: %s: invalid champion file\n", path);
		return (0);
	}
	if (reverse_bytes((int)header->prog_size) > CHAMP_MAX_SIZE)
	{
		ft_printf(2, "corewar: %s: exceeds max size\n", path);
		return (0);
	}
	return (1);
}

char		setup(t_corewar *corewar, char **args) {
	int			fd;
	void		*buffer;

	corewar->memory = ft_memalloc(MEM_SIZE);
	while (*args)
	{
		buffer = ft_memalloc(sizeof(header_t));
		if ((fd = open(*args, O_RDONLY)) == -1 ||
		read(fd, buffer, sizeof(header_t)) < 0)
		{
			ft_printf(2, "corewar: %s: invalid file\n", *args);
			return (0);
		}
		if (!check_champion(*args, buffer))
			return (0);
		args++;
	}
	return (1);
}
