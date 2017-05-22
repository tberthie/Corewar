/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 00:39:10 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/22 17:49:08 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static char		is_alive(t_corewar *corewar, t_champ *champ)
{
	int				i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
		if (corewar->proc[i]->champ == champ)
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
	text(corewar, "Processes", 0xffffff, rec(1200, 200 * (i + 1) + 80, 0, 0));
	text(corewar, "Live", 0xffffff, rec(1200, 200 * (i + 1) + 105, 0, 0));
	j = ft_parrlen((void**)corewar->proc);
	while (j--)
		if (corewar->proc[j]->champ == champ && (proc += 1))
			lives += corewar->proc[j]->live;
	text(corewar, (tmp = ft_itoabase(proc, 10)), 0xff00 + multi_color(0xff0000,
	proc / 500.0) - (proc > 500 ? multi_color(0xff00, (proc - 500.0) /
	500.0) : 0), rec(1350, 200 * (i + 1) + 80, 0, 0));
	free(tmp);
	text(corewar, (tmp = ft_itoabase(lives, 10)), 0xff00 + multi_color(0xff0000,
	lives / 1000.0) - (lives > 1000 ? multi_color(0xff00, (lives - 1000.0) /
	1000.0) : 0), rec(1350, 200 * (i + 1) + 105, 0, 0));
	free(tmp);
	subtext(corewar, champ->aff, rec(1200, 200 * (i + 1) + 150, 0, 0));
}

static void		render_players(t_corewar *corewar, int i)
{
	char			alive;
	char			*tmp;

	while (i--)
	{
		alive = is_alive(corewar, corewar->champs[i]);
		text(corewar, corewar->champs[i]->name, alive ?
		corewar->champs[i]->color : 0xa0a0a0, rec(1200, 200 * (i + 1), 0, 0));
		text(corewar, "ID", 0xffffff, rec(1200, 200 * (i + 1) + 45, 0, 0));
		text(corewar, (tmp = ft_itoabase(corewar->champs[i]->number, 10)),
		0xa0a0a0, rec(1350, 200 * (i + 1) + 45, 0, 0));
		free(tmp);
		subtext(corewar, corewar->champs[i]->comment,
		rec(1200, 200 * (i + 1) + 20, 0, 0));
		if (corewar->champs[i]->number == corewar->last_alive)
		{
			text(corewar, (tmp = ft_itoabase(corewar->champs[i]->number, 10)),
			corewar->champs[i]->color, rec(1330, 145, 0, 0));
			free(tmp);
		}
		!alive ? text(corewar, "DEAD", 0xff0000, rec(1415, 200 * (i + 1) + 45,
		0, 0)) : player_stats(corewar, i);
	}
}

static void		render_winner(t_corewar *corewar)
{
	int			i;
	SDL_Rect	rc;

	i = ft_parrlen((void**)corewar->champs);
	while (i--)
		if (corewar->last_alive == corewar->champs[i]->number)
		{
			rc = rec(15, 470, 1162, 60);
			SDL_FillRect(corewar->sf, &rc, 0x505050);
			rc = rec(15, 475, 1162, 50);
			SDL_FillRect(corewar->sf, &rc, 0);
			text(corewar, "WINNER", 0xffffff, rec(490, 485, 0, 0));
			text(corewar, corewar->champs[i]->name, corewar->champs[i]->color,
			rec(610, 495, 0, 0));
			break ;
		}
}

void			render_stats(t_corewar *corewar)
{
	char		*tmp;
	int			i;

	i = ft_parrlen((void**)corewar->proc);
	if (!i)
		render_winner(corewar);
	while (i--)
		corewar->color[corewar->proc[i]->pc] = corewar->proc[i]->champ->color;
	render_players(corewar, ft_parrlen((void**)corewar->champs));
	live_bar(corewar);
	!corewar->play ? text(corewar, "PAUSED", 0xffff00, rec(1395, 20, 0, 0)) : 0;
	text(corewar, (tmp = ft_utoabase(corewar->tot_cycle, 10)), 0xa0a0a0,
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
