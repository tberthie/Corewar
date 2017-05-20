/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:17:31 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/20 14:43:50 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static int		get_total_lives(t_corewar *corewar)
{
	int		lives;
	int		i;

	lives = 0;
	i = ft_parrlen((void**)corewar->proc);
	while (i--)
		lives += corewar->proc[i]->live;
	return (lives);
}

static int		player_bar(t_corewar *corewar, int off, int i, int total)
{
	SDL_Rect	rc;
	int			w;
	int			lives;
	int			j;

	lives = 0;
	j = ft_parrlen((void**)corewar->proc);
	while (j--)
		if (corewar->proc[j]->champ == corewar->champs[i])
			lives += corewar->proc[j]->live;
	w = ((double)lives / (double)total) * 274;
	rc = rec(1203 + off, 183, w, 4);
	SDL_FillRect(corewar->sf, &rc, corewar->champs[i]->color);
	return (off + w);
}

void			live_bar(t_corewar *corewar)
{
	SDL_Rect	rc;
	int			off;
	int			total;
	int			i;

	rc = rec(1200, 180, 280, 10);
	SDL_FillRect(corewar->sf, &rc, 0x505050);
	off = 0;
	total = get_total_lives(corewar);
	if (total)
	{
		i = ft_parrlen((void**)corewar->champs);
		while (i--)
			off = player_bar(corewar, off, i, total);
	}
}
