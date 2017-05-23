/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:17:40 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/23 14:55:29 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			*parse_champion(int fd, char *path)
{
	t_header	*header;
	void		*buffer;
	void		*data;

	buffer = ft_memalloc(sizeof(t_header));
	if (read(fd, buffer, sizeof(t_header)) != sizeof(t_header))
		error(path, E_READ);
	header = (t_header*)buffer;
	if ((rev_int(header->magic) != COREWAR_EXEC_MAGIC))
		error(path, E_FORMAT);
	if (rev_int(header->prog_size) > CHAMP_MAX_SIZE)
		error(path, E_SIZE);
	data = ft_memalloc(rev_int(header->prog_size) + sizeof(t_header));
	ft_memcpy(data, buffer, sizeof(t_header));
	if (read(fd, data + sizeof(t_header), rev_int(header->prog_size)) !=
	rev_int(header->prog_size))
		error(path, E_DIFF);
	ft_free(buffer);
	return (data);
}

static void		init_champion(t_corewar *corewar, t_champ *champ,
				t_header *header, void *data)
{
	int			color;

	champ->name = ft_strdup(header->prog_name);
	champ->comment = ft_strdup(header->comment);
	champ->size = rev_int(header->prog_size);
	champ->content = data + sizeof(t_header);
	color = ft_parrlen((void**)corewar->champs);
	champ->color = 0xff * (color == 3) + (0xff << 8) * (color == 1 ||
	color == 2 || color == 3) + (0xff << 16) * (color == 0 || color == 2);
	champ->aff = ft_strnew();
}

char			find_champion(t_champ **champs, int n)
{
	t_champ **tmp;

	tmp = champs;
	while (*tmp)
	{
		if ((*tmp)->number == n)
			return (1);
		tmp++;
	}
	return (0);
}

static void		set_number(t_corewar *corewar, t_champ *champ)
{
	int		i;

	i = -1;
	if (corewar->next > 0 && !find_champion(corewar->champs, -corewar->next))
		champ->number = -corewar->next;
	else
	{
		while (find_champion(corewar->champs, i))
			i--;
		champ->number = i;
	}
	corewar->next = 0;
}

void			add_champion(t_corewar *corewar, char *path)
{
	t_champ		*champ;
	t_header	*header;
	void		*data;
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		error(path, strerror(errno));
	data = parse_champion(fd, path);
	header = (t_header*)data;
	close(fd);
	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	init_champion(corewar, champ, header, data);
	set_number(corewar, champ);
	ft_print(1, "Champion #%d loaded: \x1b[32m%s\x1b[0m\n%s\n\n", champ->number,
	champ->name, champ->comment);
	ft_parrpush((void***)&corewar->champs, champ);
}
