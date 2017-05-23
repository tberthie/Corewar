/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:21:25 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/23 15:45:27 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		parse_option(t_corewar *corewar, char **args)
{
	if (!ft_strcmp(*args, "-dump") || !ft_strcmp(*args, "-n"))
	{
		if (!args[1])
			error(args[0], E_EXP"\n"EOC"usage: "E_USAGE);
		else if (ft_intlen(ft_atoi(args[1])) != (int)ft_strlen(args[1]) ||
		ft_atoi(args[1]) <= 0)
			error(args[1], E_NBR"\n"EOC"usage: "E_USAGE);
	}
	if (!ft_strcmp(*args, "-dump"))
		corewar->dump = (unsigned int)ft_atoi(args[1]);
	else if (!ft_strcmp(*args, "-n"))
		corewar->next = (unsigned int)ft_atoi(args[1]);
	else
		error(*args, E_ARG"\n"EOC"usage: "E_USAGE);
}

static void		parse(t_corewar *corewar, char **args)
{
	corewar->next = 0;
	while (*args)
	{
		if (!ft_strcmp(*args, "-v"))
			corewar->visual = 1;
		else if (**args == '-')
			parse_option(corewar, args++);
		else
			add_champion(corewar, *args);
		args++;
	}
}

void			setup_visual(t_corewar *visu)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) || TTF_Init() ||
	!(visu->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, 1500, 1000, SDL_WINDOW_SHOWN)) || !(visu->ren =
	SDL_CreateRenderer(visu->win, -1, SDL_RENDERER_ACCELERATED)) ||
	!(visu->hex_font = TTF_OpenFont("SDL/font.ttf", 9)) ||
	!(visu->font = TTF_OpenFont("SDL/font.ttf", 20)) ||
	!(visu->subfont = TTF_OpenFont("SDL/font.ttf", 12)))
		error(0, (char*)SDL_GetError());
	visu->sf = SDL_CreateRGBSurface(0, 1500, 1000, 32, 0, 0, 0, 0);
	visu->cps = 250;
	visu->color = ft_m(MEM_SIZE * 4);
	ft_memset(visu->color, MEM_SIZE * 4, (char)0x50);
}

void			setup(t_corewar *corewar, char **args)
{
	corewar->next = 0;
	corewar->memory = ft_memalloc(MEM_SIZE);
	corewar->champs = (t_champ**)ft_parrnew();
	corewar->proc = (t_proc**)ft_parrnew();
	corewar->dump = 0;
	corewar->ctd = CYCLE_TO_DIE;
	corewar->last_alive = 0;
	corewar->check = MAX_CHECKS;
	parse(corewar, args);
	corewar->play = corewar->visual ? 0 : 1;
	if (ft_parrlen((void**)corewar->champs) < 1)
		error(0, "Not enough champions");
	if (ft_parrlen((void**)corewar->champs) > MAX_PLAYERS)
		error(0, "Too many champions");
}
