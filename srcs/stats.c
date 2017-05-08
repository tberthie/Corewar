/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 00:39:10 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/08 16:43:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

t_champ			*get_player(t_corewar *corewar, t_proc *proc)
{
	unsigned int	nb;
	int				i;

	nb = *proc->reg;
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
		if (*corewar->proc[i]->reg == champ->number && corewar->proc[i]->alive)
			return (1);
	return (0);
}

static void		player_stats(t_corewar *corewar, int i)
{
	t_champ			*champ;
	unsigned int	lives;
	unsigned int	proc;
	char			*tmp;
	int				j;

	lives = 0;
	proc = 0;
	champ = corewar->champs[i];
	text(corewar, "Processes", 0xffffff, rec(1200, 200 * (i + 1) + 50, 0, 0));
	text(corewar, "Live", 0xffffff, rec(1200, 200 * (i + 1) + 75, 0, 0));
	j = ft_parrlen((void**)corewar->proc);
	while (j--)
	{
		if (corewar->proc[j]->alive && *corewar->proc[j]->reg ==
		champ->number && (proc += 1))
			lives += corewar->proc[j]->live;
	}
	text(corewar, (tmp = ft_itoabase(proc, 10)), 0xa0a0a0,
	rec(1350, 200 * (i + 1) + 50, 0, 0));
	free(tmp);
	text(corewar, (tmp = ft_itoabase(lives, 10)), 0xa0a0a0,
	rec(1350, 200 * (i + 1) + 75, 0, 0));
	free(tmp);
}

static void		render_players(t_corewar *corewar)
{
	int				i;
	char			alive;
	char			*tmp;

	i = ft_parrlen((void**)corewar->champs);
	while (i--)
	{
		alive = is_alive(corewar, corewar->champs[i]);
		text(corewar, corewar->champs[i]->name, alive ?
		corewar->champs[i]->color : 0xa0a0a0, rec(1200, 200 * (i + 1), 0, 0));
		text(corewar, "#", 0xa0a0a0, rec(1200, 200 * (i + 1) + 20, 0, 0));
		text(corewar, (tmp = ft_itoabase(corewar->champs[i]->number, 10)),
		0xa0a0a0, rec(1220, 200 * (i + 1) + 20, 0, 0));
		free(tmp);
		if (corewar->champs[i]->number == corewar->last_alive)
		{
			text(corewar, "#", corewar->champs[i]->color, rec(1330, 145, 0, 0));
			text(corewar, (tmp = ft_itoabase(corewar->champs[i]->number, 10)),
			corewar->champs[i]->color, rec(1350, 145, 0, 0));
			free(tmp);
		}
		!alive ? text(corewar, "DEAD", 0xff0000, rec(1415, 200 * (i + 1), 0, 0))
		: player_stats(corewar, i);
	}
}

void			render_stats(t_corewar *corewar)
{
	t_champ		*player;
	char		*tmp;
	int			i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
	{
		if (corewar->proc[i]->alive &&
		(player = get_player(corewar, corewar->proc[i])))
			corewar->color[corewar->proc[i]->pc] = player->color;
	}
	render_players(corewar);
	!corewar->play ? text(corewar, "PAUSED", 0xffff00, rec(1395, 20, 0, 0)) : 0;
	text(corewar, (tmp = ft_utoabase(corewar->cycle, 10)), 0xa0a0a0,
	rec(1330, 60, 0, 0));
	free(tmp);
	text(corewar, (tmp = ft_utoabase(corewar->ctd, 10)), 0xa0a0a0,
	rec(1330, 85, 0, 0));
	free(tmp);
	text(corewar, (tmp = ft_utoabase(corewar->cps, 10)), 0xa0a0a0,
	rec(1330, 110, 0, 0));
	free(tmp);
	text(corewar, "Last live", 0xffffff, rec(1200, 145, 0, 0));
}
