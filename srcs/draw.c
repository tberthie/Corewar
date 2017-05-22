/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:22:22 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/17 16:41:17 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

SDL_Rect		rec(int x, int y, int w, int h)
{
	SDL_Rect	rc;

	rc.x = x;
	rc.y = y;
	rc.w = w;
	rc.h = h;
	return (rc);
}

SDL_Color		get_color(unsigned int color)
{
	SDL_Color	sc;

	sc.r = (color >> 16) & 0xff;
	sc.g = (color >> 8) & 0xff;
	sc.b = color & 0xff;
	return (sc);
}

void			dhex(t_corewar *corewar, char *txt, unsigned int color,
				SDL_Rect rc)
{
	SDL_Surface		*sf;

	sf = TTF_RenderText_Shaded(corewar->hex_font, txt, color == 0x50505050 ?
	get_color(0xa0a0a0) : get_color(0x101010), get_color(color));
	SDL_BlitSurface(sf, 0, corewar->sf, &rc);
	SDL_FreeSurface(sf);
}

void			text(t_corewar *corewar, char *txt, unsigned int color,
				SDL_Rect rc)
{
	SDL_Surface		*sf;

	sf = TTF_RenderText_Shaded(corewar->font, txt, get_color(color),
	get_color(0));
	SDL_BlitSurface(sf, 0, corewar->sf, &rc);
	SDL_FreeSurface(sf);
}

void			subtext(t_corewar *corewar, char *txt, SDL_Rect rc)
{
	SDL_Surface		*sf;

	sf = TTF_RenderText_Shaded(corewar->subfont, txt, get_color(0xa0a0a0),
	get_color(0));
	SDL_BlitSurface(sf, 0, corewar->sf, &rc);
	SDL_FreeSurface(sf);
}
