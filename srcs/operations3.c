/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:48:56 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/23 15:07:07 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int		move_pc(int tab, unsigned char op)
{
	if (tab == 1)
		return (1);
	else if (tab == 2)
	{
		if ((9 <= op && op <= 12) || op == 14 || op == 15)
			return (2);
		else
			return (4);
	}
	else
		return (2);
}

int		*byte_analysis(void *adr)
{
	int				*nbr;
	unsigned char	byte;

	byte = *(unsigned char*)(adr);
	nbr = (int*)malloc(sizeof(int) * 3);
	nbr[0] = (byte >> 6) & (REG_CODE | DIR_CODE | IND_CODE);
	nbr[1] = (byte >> 4) & (REG_CODE | DIR_CODE | IND_CODE);
	nbr[2] = (byte >> 2) & (REG_CODE | DIR_CODE | IND_CODE);
	if ((1 <= nbr[0] && nbr[0] <= 3) && (1 <= nbr[1] && nbr[1] <= 3))
		return (nbr);
	free(nbr);
	return (NULL);
}

int		set_index(void *adr)
{
	int		index;

	index = *(char*)(adr);
	if (index < 1 || 16 < index)
		return (-1);
	else
		return (index - 1);
}

void	return_error(t_proc *processus, int *tab)
{
	processus->pc = set_pc(processus->pc + 1);
	free(tab);
}

void	change_carry(t_proc *processus, int p1)
{
	if (p1 == 0)
		processus->carry = 1;
	else
		processus->carry = 0;
}
