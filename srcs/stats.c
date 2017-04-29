/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 00:39:10 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 17:28:22 by tberthie         ###   ########.fr       */
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

static char		is_alive(t_corewar *corewar, t_champ *champ)
{
	int				i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
		if (*(unsigned int*)(corewar->proc[i]->reg[0]) == champ->number &&
		corewar->proc[i]->alive)
			return (1);
	return (0);
}

static void		player_stats(t_corewar *corewar, t_visual *visu, int i)
{
	t_champ			*champ;
	unsigned int	lives;
	unsigned int	proc;
	char			*tmp;
	int				j;

	lives = 0;
	proc = 0;
	champ = corewar->champs[i];
	text(visu, "Processes", 0xffffff, rec(1200, 200 * (i + 1) + 50, 0, 0));
	text(visu, "Live", 0xffffff, rec(1200, 200 * (i + 1) + 75, 0, 0));
	j = ft_parrlen((void**)corewar->proc);
	while (j--)
	{
		if (corewar->proc[j]->alive && *(unsigned int*)corewar->proc[j]->reg[0]
		== champ->number && (proc += 1))
			lives += corewar->proc[j]->live;
	}
	text(visu, (tmp = ft_itoabase(proc, 10)), 0xa0a0a0,
	rec(1320, 200 * (i + 1) + 50, 0, 0));
	free(tmp);
	text(visu, (tmp = ft_itoabase(lives, 10)), 0xa0a0a0,
	rec(1320, 200 * (i + 1) + 75, 0, 0));
	free(tmp);
}

static void		render_players(t_corewar *corewar, t_visual *visu)
{
	int				i;
	char			alive;

	i = ft_parrlen((void**)corewar->champs);
	while (i--)
	{
		alive = is_alive(corewar, corewar->champs[i]);
		text(visu, corewar->champs[i]->name, alive ? corewar->champs[i]->color :
		0xa0a0a0, rec(1200, 200 * (i + 1), 0, 0));
		if (corewar->champs[i]->number == corewar->last_alive)
			text(visu, corewar->champs[i]->name, corewar->champs[i]->color,
			rec(1300, 145, 0, 0));
		if (!alive)
			text(visu, "DEAD", 0xff0000, rec(1415, 200 * (i + 1), 0, 0));
		else
			player_stats(corewar, visu, i);
	}
}

void			render_stats(t_corewar *corewar, t_visual *visu)
{
	t_champ		*player;
	char		*tmp;
	int			i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
	{
		if ((player = get_player(corewar, corewar->proc[i])))
			visu->color[corewar->proc[i]->pc] = player->color;
	}
	render_players(corewar, visu);
	!corewar->play ? text(visu, "PAUSED", 0xffff00, rec(1395, 60, 0, 0)) : 0;
	text(visu, (tmp = ft_utoabase(corewar->cycle, 10)), 0xa0a0a0,
	rec(1300, 60, 0, 0));
	free(tmp);
	text(visu, (tmp = ft_utoabase(corewar->ctd, 10)), 0xa0a0a0,
	rec(1300, 85, 0, 0));
	free(tmp);
	text(visu, (tmp = ft_utoabase(visu->cps, 10)), 0xa0a0a0,
	rec(1300, 110, 0, 0));
	free(tmp);
	text(visu, "Last live", 0xffffff, rec(1200, 145, 0, 0));
}
