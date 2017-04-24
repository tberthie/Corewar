/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:57:55 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/24 17:36:05 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#include "libft.h"

#include <fcntl.h>
#include <unistd.h>

static char		check_header(header_t *header, char *path)
{
	if ((rev_int(header->magic) != COREWAR_EXEC_MAGIC))
	{
		ft_printf(2, "corewar: %s\n"RED""E_FORMAT"\n"EOC, path);
		return (0);
	}
	if (rev_int(header->prog_size) > CHAMP_MAX_SIZE)
	{
		ft_printf(2, "corewar: %s\n"RED""E_SIZE"\n"EOC, path);
		return (0);
	}
	return (1);
}

static void		*get_champion(int fd, char *path)
{
	header_t	*header;
	void		*buffer;
	void		*data;

	buffer = ft_memalloc(sizeof(header_t));
	if (read(fd, buffer, sizeof(header_t)) != sizeof(header_t))
	{
		ft_printf(2, "corewar: %s\n"RED""E_READ"\n"EOC, path);
		return (0);
	}
	if (!check_header((header = (header_t*)buffer), path))
		return (0);
	data = ft_memalloc(rev_int(header->prog_size) + sizeof(header_t));
	ft_memcpy(data, buffer, sizeof(header_t));
	if (read(fd, data + sizeof(header_t), rev_int(header->prog_size)) !=
	rev_int(header->prog_size))
	{
		ft_printf(2, "corewar: %s\n"RED""E_READ"\n"EOC, path);
		return (0);
	}
	ft_free(buffer);
	return (data);
}

static void		add_champion(t_corewar *corewar, header_t *header, void *data)
{
	ft_printf(1, "\n%s\n", header->prog_name);
	ft_printf(1, "%s\n", header->comment);
	ft_printf(1, "Size %do\n", rev_int(header->prog_size));
}

static char		parse(t_corewar *corewar, char **args)
{
	void		*data;
	int			fd;

	while (*args)
	{
		if ((fd = open(*args, O_RDONLY)) < 0)
		{
			ft_printf(2, "corewar: %s\n"RED""E_OPEN"\n"EOC, *args);
			return (0);
		}
		if (!(data = get_champion(fd, *args)))
			return (0);
		close(fd);
		add_champion(corewar, (header_t*)data, data + sizeof(header_t));
		ft_free(data);
		args++;
	}
	return (1);
}

char				setup(t_corewar *corewar, char **args)
{
	corewar->memory = ft_memalloc(MEM_SIZE);
	if (!parse(corewar, args))
		return (0);
	return (1);
}
