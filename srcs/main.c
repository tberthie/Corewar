/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/20 14:29:14 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#include "libft.h"

int			main(int ac, char **av) {
	t_corewar	*corewar;

	corewar = (t_corewar*)ft_m(sizeof(t_corewar));
	if (setup(corewar, ++av))
	{

	}
	else
		ft_printf(2, "corewar: an error occured\n");
	return (0);
}
