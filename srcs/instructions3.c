/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:44 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/07 16:19:02 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"
#include <stdio.h>

void 	print_bit(void *adr, int p1)
{
	int		i;

	i = 4;
	while (i--)
	{
		*(unsigned char*)adr++ = (p1 >> (8 * i)) & 0xff;
	}
}

void	sti(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		tmp;
	int		p1;
	int		p2;
	int		p3;
	int		pc;

	pc = processus->pc;
	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_reg_value(processus, corewar);
		// ft_printf(1, "STI VALUE= %d\n", p1);
		// printf("STI VALUE HEXA = %.4x\n", (int)p1);
		p2 = get_value(processus, corewar, tab[1], op);
		p3 = get_value(processus, corewar, tab[2], op);
		tmp = set_pc(p2 + p3 + pc);
		// ft_printf(1, "STIII OFFSET = %d\n", tmp);
		print_bit(corewar->memory + tmp, p1);
	}
	processus->pc++;
}

int		set_index(t_proc *processus, t_corewar *corewar)
{
	int		index;

	index = *(char*)(corewar->memory + processus->pc);
	if (index < 1 || 16 < index)
	{
		processus->carry = 0;
		processus->pc++;
		return (-1);
	}
	else
	{
		processus->pc++;
		return (index - 1);
	}
}

void	add(t_proc *processus, t_corewar *corewar)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		p1 = *(int*)processus->reg[index];
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		p2 = *(int*)processus->reg[index];
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		*(int*)processus->reg[index] = p1 + p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	sub(t_proc *processus, t_corewar *corewar)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		p1 = *(int*)processus->reg[index];
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		p2 = *(int*)processus->reg[index];
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		*(int*)processus->reg[index] = p1 - p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}
