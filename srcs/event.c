/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:58:09 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/28 17:16:35 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		quit(void)
{
	SDL_Quit();
	exit(0);
}

static void		process_event(SDL_Event ev)
{
	if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_CLOSE)
		quit();
}

static void		keyboard(t_corewar *corewar, t_visual *visu)
{
	const Uint8		*status;

	status = SDL_GetKeyboardState(0);
	status[SDL_SCANCODE_ESCAPE] ? quit() : 0;
}

void			event(t_corewar *corewar, t_visual *visu)
{
	SDL_Event	ev;

	keyboard(corewar, visu);
	while (SDL_PollEvent(&ev))
		process_event(ev);
}
