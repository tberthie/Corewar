/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 18:01:57 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			main(int ac, char **av)
{
	t_corewar	*corewar;
	t_visual	*visu;

	if (ac > MAX_ARGS_NUMBER + 1)
		error(0, "Too many arguments");
	if (ac < 2)
		error("usage", EOC""E_USAGE);
	corewar = (t_corewar*)ft_memalloc(sizeof(t_corewar));
	setup(corewar, ++av);
	load(corewar);
	if (corewar->visual)
	{
		setup_visual((visu = (t_visual*)ft_memalloc(sizeof(t_visual))));
		visual_run(corewar, visu);
	}
	else
		run(corewar);
	return (0);
}
