/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/04 15:06:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			main(int ac, char **av)
{
	t_corewar	*corewar;

	if (ac > MAX_ARGS_NUMBER + 1)
		error(0, "Too many arguments");
	if (ac < 2)
		error("usage", EOC""E_USAGE);
	corewar = (t_corewar*)ft_memalloc(sizeof(t_corewar));
	setup(corewar, ++av);
	load(corewar);
	if (corewar->visual)
	{
		setup_visual(corewar);
		visual_run(corewar);
	}
	else
		run(corewar);
	return (0);
}
