/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:55:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/23 14:51:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			set_visual(t_corewar *corewar)
{
	SDL_Rect	rc;

	rc = rec(0, 0, 1500, 1000);
	SDL_FillRect(corewar->sf, &rc, 0);
	rc = rec(15, 15, 1162, 970);
	SDL_FillRect(corewar->sf, &rc, 0x505050);
	event(corewar);
}

void			display(t_corewar *corewar)
{
	SDL_Texture		*tx;

	render_hex(corewar);
	text(corewar, "C O R E W A R", 0xffffff, rec(1200, 20, 0, 0));
	text(corewar, "Cycles", 0xffffff, rec(1200, 60, 0, 0));
	text(corewar, "To Die", 0xffffff, rec(1200, 85, 0, 0));
	text(corewar, "CPS Max", 0xffffff, rec(1200, 110, 0, 0));
	text(corewar, "Last live", 0xffffff, rec(1200, 145, 0, 0));
	render_stats(corewar);
	tx = SDL_CreateTextureFromSurface(corewar->ren, corewar->sf);
	SDL_RenderCopy(corewar->ren, tx, 0, 0);
	SDL_DestroyTexture(tx);
	SDL_RenderPresent(corewar->ren);
}

static void		calc_cps(t_corewar *corewar)
{
	double		delay;
	double		frames;

	if (!corewar->step--)
	{
		delay = SDL_GetTicks();
		display(corewar);
		delay = 1000.0 / (SDL_GetTicks() - delay);
		frames = corewar->cps / delay;
		if (frames < 1.0)
			SDL_Delay(1000.0 / (frames * delay));
		corewar->step = frames >= 0.5 && frames < 1.0 ? 1 : frames;
	}
}

void			set_ctd(t_corewar *corewar, unsigned int cycle)
{
	if (cycle >= corewar->ctd && (check_live(corewar)
	>= NBR_LIVE || corewar->check <= 0))
	{
		corewar->ctd -= CYCLE_DELTA > corewar->ctd ?
		corewar->ctd : CYCLE_DELTA;
		corewar->check = MAX_CHECKS;
	}
	else
		--corewar->check;
}

void			visual_run(t_corewar *corewar)
{
	corewar->step = 0;
	while (ft_parrlen((void**)corewar->proc))
	{
		set_visual(corewar);
		if (corewar->play)
		{
			process(corewar);
			if (++corewar->tot_cycle == corewar->dump)
				dump(corewar);
			set_ctd(corewar, ++corewar->cycle);
			corewar->cycle = corewar->cycle >= corewar->ctd ? 0 :
			corewar->cycle;
		}
		corewar->play ? calc_cps(corewar) : display(corewar);
	}
	corewar->dump > corewar->tot_cycle ? dump(corewar) : 0;
	display(corewar);
	while (1)
		event(corewar);
}
