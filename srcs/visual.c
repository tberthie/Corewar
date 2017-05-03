/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:55:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/03 17:17:54 by tberthie         ###   ########.fr       */
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
}

static void		display(t_corewar *corewar, t_visual *visu)
{
	SDL_Texture		*tx;

	render_hex(corewar, visu);
	text(visu, "C O R E W A R", 0xffffff, rec(1200, 20, 0, 0));
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

static void		calc_cps(t_corewar *corewar, t_visual *visu)
{
	double		delay;
	double		frames;

	if (!visu->step--)
	{
		delay = SDL_GetTicks();
		display(corewar, visu);
		delay = 1000.0 / (SDL_GetTicks() - delay);
		frames = visu->cps / delay;
		if (frames < 1.0)
			SDL_Delay(1000.0 / (frames * delay));
		visu->step = frames >= 0.5 && frames < 1.0 ? 1 : frames +
		(frames - (int)frames >= 0.5 ? 1 : 0);
	}
}

void			visual_run(t_corewar *corewar, t_visual *visu)
{
	unsigned int	cycle;
	unsigned int	lives;

	cycle = 0;
	visu->step = 0;
	while (alive_proc(corewar->proc))
	{
		set_visual(corewar, visu);
		if (corewar->play)
		{
			process(corewar, visu);
			corewar->cycle++;
			cycle++;
			if ((cycle >= corewar->ctd && (lives = check_live(corewar, visu,
			corewar->proc)) >= NBR_LIVE) || !--corewar->check)
				set_ctd(corewar);
			cycle = cycle >= corewar->ctd ? 0 : cycle;
		}
		corewar->play ? calc_cps(corewar, visu) : display(corewar, visu);
	}
	display(corewar, visu);
	while (1)
		event(corewar, visu);
}
