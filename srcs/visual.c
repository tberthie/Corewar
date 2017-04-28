/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:55:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/28 18:51:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		render_hex(t_corewar *corewar, t_visual *visu)
{
	SDL_Rect	rc;
	int			y[2];
	int			x[2];
	int			rows;

	rows = MEM_SIZE / 64;
	y[0] = 0;
	while (y[0] < rows)
	{
		x[0] = 0;
		while (x[0] < 64)
		{
			x[1] = ((double)x[0] / 64) * 1500.0 - 0.75;
			y[1] = ((double)y[0] / rows) * 1000.0 - 0.75;
			rc = rec(x[1], y[1], (1.0 / 64.0 * 1500.0), (1.0 / rows) * 1000.0);
			SDL_FillRect(visu->sf, &rc, 0xa00000);
//			text(visu, "00", 0xffffff, rc);
			x[0]++;
		}
		y[0]++;
	}
}

static void		set_visual(t_corewar *corewar, t_visual *visu)
{
	SDL_Rect	rc;

	event(corewar, visu);
	ft_memcpy(visu->save, corewar->memory, MEM_SIZE);
	rc = rec(0, 0, 1500, 1000);
	SDL_FillRect(visu->sf, &rc, 0);
	render_hex(corewar, visu);
}

static void		display(t_visual *visu)
{
	SDL_Texture		*tx;

	tx = SDL_CreateTextureFromSurface(visu->ren, visu->sf);
	SDL_RenderCopy(visu->ren, tx, 0, 0);
	SDL_DestroyTexture(tx);
	SDL_RenderPresent(visu->ren);
}

void			visual_run(t_corewar *corewar, t_visual *visu)
{
	unsigned int	cycle;
	unsigned int	lives;

	cycle = 0;
	while (alive_proc(corewar->proc))
	{
		set_visual(corewar, visu);
		if (corewar->play)
		{
			process(corewar);
			cycle++;
			if ((cycle >= corewar->ctd && (lives = check_live(corewar->proc)) >=
			NBR_LIVE) || !--corewar->check)
			{
				corewar->ctd -= CYCLE_DELTA > corewar->ctd ?
				corewar->ctd : CYCLE_DELTA;
				corewar->check = MAX_CHECKS;
			}
			cycle = cycle >= corewar->ctd ? 0 : cycle;
		}
		display(visu);
	}
	SDL_Quit();
}

