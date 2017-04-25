/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:57:55 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/25 16:20:09 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		*parse_champion(int fd, char *path)
{
	header_t	*header;
	void		*buffer;
	void		*data;

	buffer = ft_memalloc(sizeof(header_t));
	if (read(fd, buffer, sizeof(header_t)) != sizeof(header_t))
		error(path, E_READ);
	header = (header_t*)buffer;
	if ((rev_int(header->magic) != COREWAR_EXEC_MAGIC))
		error(path, E_FORMAT);
	if (rev_int(header->prog_size) > CHAMP_MAX_SIZE)
		error(path, E_SIZE);
	data = ft_memalloc(rev_int(header->prog_size) + sizeof(header_t));
	ft_memcpy(data, buffer, sizeof(header_t));
	if (read(fd, data + sizeof(header_t), rev_int(header->prog_size)) !=
	rev_int(header->prog_size))
		error(path, E_READ);
	ft_free(buffer);
	return (data);
}

static void		add_champion(t_corewar *corewar, char *path)
{
	t_champ		*champ;
	header_t	*header;
	void		*data;
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		error(path, strerror(errno));
	data = parse_champion(fd, path);
	header = (header_t*)data;
	close(fd);
	champ = (t_champ*)ft_m(sizeof(t_champ));
	champ->name = ft_strdup(header->prog_name);
	champ->comment = ft_strdup(header->comment);
	champ->size = header->prog_size;
	champ->content = data + sizeof(header_t);
	//champ->number = n;
	ft_parrpush((void***)&corewar->champs, champ);
}

/*static int		parse_option(t_corewar *corewar, char **args)
{
	if (!ft_strcmp(*args, "-dump"))
	{
		
	}
	else if (!ft_strcmp(*args, "-n"))
	{
		if (!args[1] || ft_intlen(ft_atoi(args[1])) != (int)ft_strlen(args[1]))
			error(*args, E_PARSE);
		else
			return (ft_atoi(args[1]));
	}
	else
		error(*args, E_OPTION"\n"EOC"usage: "E_USAGE);
	return (0);
}*/

static void		parse(t_corewar *corewar, char **args)
{
	while (*args)
	{
		add_champion(corewar, *args);
		args++;
	}
}

void			setup(t_corewar *corewar, char **args)
{
	corewar->memory = ft_memalloc(MEM_SIZE);
	corewar->champs = (t_champ**)ft_parrnew();
	parse(corewar, args);
	if (ft_parrlen((void**)corewar->champs) < 2)
		error(0, "Not enough champions");
	if (ft_parrlen((void**)corewar->champs) > MAX_PLAYERS)
		error(0, "Too many champions");
}
