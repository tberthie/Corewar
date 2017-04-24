/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/24 15:13:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#include "libft.h"

int			main(int ac, char **av) {
	t_corewar	*corewar;

	corewar = (t_corewar*)ft_memalloc(sizeof(t_corewar));
	if (setup(corewar, ++av))
	{

	}
	return (0);
}
