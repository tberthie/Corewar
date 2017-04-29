/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 00:39:10 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 14:51:41 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static t_champ	*get_player(t_corewar *corewar, t_proc *proc)
{
	unsigned int	nb;
	int				i;

	nb = *(char*)(*proc->reg);
	i = ft_parrlen((void**)corewar->champs);
	while (i--)
	{
		if (corewar->champs[i]->number == nb)
			return (corewar->champs[i]);
	}
	return (0);
}

void			render_stats(t_corewar *corewar, t_visual *visu)
{
	t_champ		*player;
	int			i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
	{
		if ((player = get_player(corewar, corewar->proc[i])))
			visu->color[corewar->proc[i]->pc] = player->color;
	}
	text(visu, "fluttershy", 0xff0000, rec(1300, 145, 0, 0));

	text(visu, "1 - fluttershy", 0xa0a0a0, rec(1200, 200, 0, 0));
	text(visu, "DEAD", 0xff0000, rec(1415, 200, 0, 0));

	text(visu, "2 - helltrain", 0x00ff00, rec(1200, 400, 0, 0));

	text(visu, "3 - zork", 0xa0a0a0, rec(1200, 600, 0, 0));

	text(visu, "DEAD", 0xff0000, rec(1415, 600, 0, 0));
	text(visu, "4 - rainbowdash", 0xff00ff, rec(1200, 800, 0, 0));
}
