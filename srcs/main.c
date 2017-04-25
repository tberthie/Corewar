/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/25 16:20:22 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int			main(int ac, char **av)
{
	t_corewar	*corewar;

	if (ac > MAX_ARGS_NUMBER + 1)
		error(0, "Too many arguments");
	corewar = (t_corewar*)ft_memalloc(sizeof(t_corewar));
	setup(corewar, ++av);
	return (0);
}
