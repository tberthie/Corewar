/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:57:55 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/26 13:52:58 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		parse_option(t_corewar *corewar, char **args)
{
	if (!ft_strcmp(*args, "-dump"))
	{
		if (!args[1])
			error(args[0], E_ARG"\n"EOC"usage: "E_USAGE);
		else if (ft_intlen((int)(corewar->dump =
		(unsigned int)ft_atoi(args[1]))) != (int)ft_strlen(args[1]))
			error(args[1], E_ARG"\n"EOC"usage: "E_USAGE);
	}
	else
		error(*args, E_ARG"\n"EOC"usage: "E_USAGE);
}

static void		parse(t_corewar *corewar, char **args)
{
	while (*args)
	{
		if (**args == '-')
			parse_option(corewar, args++);
		else
			add_champion(corewar, *args);
		args++;
	}
}

void			setup(t_corewar *corewar, char **args)
{
	corewar->memory = ft_memalloc(MEM_SIZE);
	corewar->champs = (t_champ**)ft_parrnew();
	parse(corewar, args);
	if (ft_parrlen((void**)corewar->champs) < 2)
		error(0, "Not enough champions");
	if (ft_parrlen((void**)corewar->champs) > MAX_PLAYERS)
		error(0, "Too many champions");
}
