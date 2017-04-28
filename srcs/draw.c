/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:22:22 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/28 18:27:44 by tberthie         ###   ########.fr       */
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

void			text(t_visual *visu, char *txt, unsigned int color, SDL_Rect rc)
{
	SDL_Surface		*sf;

	sf = TTF_RenderText_Solid(visu->font, txt, get_color(color));
	SDL_BlitSurface(sf, 0, visu->sf, &rc);
	SDL_FreeSurface(sf);
}
