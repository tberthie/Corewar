/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:44 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/15 16:51:22 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"
#include <stdio.h>

void 	print_bit(void *adr, int p1)
{
	// *(unsigned int*)adr = rev_int(p1);
	*(unsigned int*)adr = p1;
}

void	sti(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		tmp;
	unsigned int		p1;
	int		p2;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		p1 = get_reg_value(processus, corewar->memory + pc);
		pc++;
		p2 = get_value(processus, corewar, tab[1], op, corewar->memory + pc);
		pc += move_pc(tab[1], op);
		p2 += get_value(processus, corewar, tab[2], op, corewar->memory + pc);
		tmp = set_pc(p2 + processus->pc);
		print_bit(corewar->memory + tmp, p1);
		change_carry(processus, p1);
		processus->pc = set_pc(pc + move_pc(tab[2], op));
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	add(t_proc *processus, t_corewar *corewar)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		pc++;
		p1 = processus->reg[index];
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		pc++;
		p2 = processus->reg[index];
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		ft_print(1, "P1 = %d && P2 = %d dans le registre: %d\n", p1, p2, index + 1);
		processus->reg[index] = p1 + p2;
		change_carry(processus, p1 + p2);
		processus->pc = set_pc(pc + 1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	sub(t_proc *processus, t_corewar *corewar)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		pc++;
		p1 = processus->reg[index];
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		pc++;
		p2 = processus->reg[index];
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		ft_print(1, "P1 = %d && P2 = %d dans le registre: %d\n", p1, p2, index + 1);
		processus->reg[index] = p1 - p2;
		change_carry(processus, p1 - p2);
		processus->pc = set_pc(pc + 1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
