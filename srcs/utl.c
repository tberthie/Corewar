/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:14:05 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/25 15:34:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			error(char *file, char *msg)
{
	if (file)
	{
		ft_printf(2, "corewar: %s\n", file);
		ft_printf(2, RED"%s\n"EOC, msg);
	}
	else
	{
		ft_printf(2, "corewar: execution failed\n", file);
		ft_printf(2, RED"%s\n"EOC, msg);
	}
	exit(EXIT_FAILURE);
}
