/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:58:09 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 00:25:32 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		quit(void)
{
	SDL_Quit();
	exit(0);
}

static void		process_event(SDL_Event ev, t_corewar *corewar)
{
	if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_CLOSE)
		quit();
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == SDLK_SPACE)
			corewar->play = !corewar->play;
	}
}

static void		keyboard(t_visual *visu)
{
	const Uint8		*status;

	status = SDL_GetKeyboardState(0);
	status[SDL_SCANCODE_ESCAPE] ? quit() : 0;
	status[SDL_SCANCODE_Q] ? visu->cps -= visu->cps > 1 : 0;
	status[SDL_SCANCODE_E] ? visu->cps++ : 0;
}

void			event(t_corewar *corewar, t_visual *visu)
{
	SDL_Event	ev;

	keyboard(visu);
	while (SDL_PollEvent(&ev))
		process_event(ev, corewar);
}
