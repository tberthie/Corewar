/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:17:40 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/26 18:27:19 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			*parse_champion(int fd, char *path)
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

static void		init_champion(t_champ *champ, header_t *header, void *data)
{
	champ->name = ft_strdup(header->prog_name);
	champ->comment = ft_strdup(header->comment);
	champ->size = rev_int(header->prog_size);
	champ->content = data + sizeof(header_t);
}

char			find_champion(t_champ **champs, unsigned int n)
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
	unsigned int	i;

	i = 1;
	if (corewar->next > 0 && !find_champion(corewar->champs, corewar->next))
		champ->number = corewar->next;
	else
	{
		while (find_champion(corewar->champs, i))
			i++;
		champ->number = i;
	}
	corewar->next = 0;
}

void			add_champion(t_corewar *corewar, char *path)
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
	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	init_champion(champ, header, data);
	set_number(corewar, champ);
	ft_parrpush((void***)&corewar->champs, champ);
}
