/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:55:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 14:48:24 by tberthie         ###   ########.fr       */
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

static void		outlines(t_visual *visu)
{
	SDL_SetRenderDrawColor(visu->ren, 0xd0, 0xd0, 0xd0, 0xff);
	SDL_RenderDrawLine(visu->ren, 10, 10, 1182, 10);
	SDL_RenderDrawLine(visu->ren, 10, 990, 1182, 990);
	SDL_RenderDrawLine(visu->ren, 10, 10, 10, 990);
	SDL_RenderDrawLine(visu->ren, 1182, 10, 1182, 990);
	SDL_RenderDrawLine(visu->ren, 1190, 10, 1190, 990);
	SDL_RenderDrawLine(visu->ren, 1490, 10, 1490, 990);
	SDL_RenderDrawLine(visu->ren, 1190, 10, 1490, 10);
	SDL_RenderDrawLine(visu->ren, 1190, 990, 1490, 990);
}

static void		display(t_corewar *corewar, t_visual *visu)
{
	SDL_Texture		*tx;
	char			*tmp;

	text(visu, "C O R E W A R", 0x900000, rec(1200, 20, 0, 0));
	text(visu, "Cycles", 0xffffff, rec(1200, 60, 0, 0));
	text(visu, (tmp = ft_utoabase(corewar->cycle, 10)), 0xa0a0a0,
	rec(1300, 60, 0, 0));
	free(tmp);
	text(visu, "To Die", 0xffffff, rec(1200, 85, 0, 0));
	text(visu, (tmp = ft_utoabase(corewar->ctd, 10)), 0xa0a0a0,
	rec(1300, 85, 0, 0));
	free(tmp);
	text(visu, "CPS Max", 0xffffff, rec(1200, 110, 0, 0));
	text(visu, (tmp = ft_utoabase(visu->cps, 10)), 0xa0a0a0,
	rec(1300, 110, 0, 0));
	free(tmp);
	text(visu, "Last live", 0xffffff, rec(1200, 145, 0, 0));
	render_stats(corewar, visu);
	tx = SDL_CreateTextureFromSurface(visu->ren, visu->sf);
	SDL_RenderCopy(visu->ren, tx, 0, 0);
	SDL_DestroyTexture(tx);
	outlines(visu);
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
