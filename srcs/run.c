/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/26 17:39:52 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void			run(t_corewar *corewar)
{
	int		i = 0;

	while (corewar->proc[i])
	{
		printf("Proc #%d %p p%d\n", i, corewar->proc[i]->pc,
		*(unsigned int*)corewar->proc[i]->reg[0]);
		i++;
	}
}
