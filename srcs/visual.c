/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:55:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 17:16:56 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		set_visual(t_corewar *corewar, t_visual *visu)
{
	SDL_Rect	rc;

	event(corewar, visu);
	ft_memcpy(visu->save, corewar->memory, MEM_SIZE);
	rc = rec(0, 0, 1500, 1000);
	SDL_FillRect(visu->sf, &rc, 0);
	rc = rec(15, 15, 1162, 970);
	SDL_FillRect(visu->sf, &rc, 0x505050);
	render_hex(corewar, visu);
}

static void		display(t_corewar *corewar, t_visual *visu)
{
	SDL_Texture		*tx;

	text(visu, "C O R E W A R", 0xffffff, rec(1200, 20, 0, 0));
	!corewar->play ? text(visu, "PAUSED", 0xffff00, rec(1395, 60, 0, 0)) : 0;
	text(visu, "Cycles", 0xffffff, rec(1200, 60, 0, 0));
	text(visu, "To Die", 0xffffff, rec(1200, 85, 0, 0));
	text(visu, "CPS Max", 0xffffff, rec(1200, 110, 0, 0));
	text(visu, "Last live", 0xffffff, rec(1200, 145, 0, 0));
	render_stats(corewar, visu);
	tx = SDL_CreateTextureFromSurface(visu->ren, visu->sf);
	SDL_RenderCopy(visu->ren, tx, 0, 0);
	SDL_DestroyTexture(tx);
	SDL_RenderPresent(visu->ren);
}

static void		set_ctd(t_corewar *corewar)
{
	corewar->ctd -= CYCLE_DELTA > corewar->ctd ?
	corewar->ctd : CYCLE_DELTA;
	corewar->check = MAX_CHECKS;
}

void			visual_run(t_corewar *corewar, t_visual *visu)
{
	unsigned int	cycle;
	unsigned int	lives;
	unsigned int	time;

	cycle = 0;
	while (alive_proc(corewar->proc))
	{
		set_visual(corewar, visu);
		if (corewar->play)
		{
			time = SDL_GetTicks();
			process(corewar);
			corewar->cycle++;
			cycle++;
			if ((cycle >= corewar->ctd && (lives = check_live(corewar->proc)) >=
			NBR_LIVE) || !--corewar->check)
				set_ctd(corewar);
			cycle = cycle >= corewar->ctd ? 0 : cycle;
			(time = SDL_GetTicks() - time) < 1000 / visu->cps ?
			SDL_Delay(1000 / visu->cps - time) : 0;
		}
		display(corewar, visu);
	}
	while (1)
		event(corewar, visu);
}
