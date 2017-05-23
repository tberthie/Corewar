/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:44 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/23 15:07:14 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	sti(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int				*tab;
	int				tmp;
	unsigned int	p1;
	int				p2;
	int				pc;

	pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(corewar->memory + pc++)))
	{
		p1 = get_reg_value(processus, corewar->memory + pc);
		pc = set_pc(pc + 1);
		p2 = get_value(processus, tab[1], op, corewar->memory + pc);
		pc = set_pc(pc + move_pc(tab[1], op));
		p2 += get_value(processus, tab[2], op, corewar->memory + pc);
		tmp = set_pc(p2 + processus->pc);
		print_bit(corewar, tmp, p1);
		processus->pc = set_pc(pc + move_pc(tab[2], op));
		free(tab);
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

	pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(corewar->memory + pc++)))
	{
		if ((index = set_index(corewar->memory + pc)) < 0)
			return (return_error(processus, tab));
		pc = set_pc(pc + 1);
		p1 = processus->reg[index];
		if ((index = set_index(corewar->memory + pc++)) < 0)
			return (return_error(processus, tab));
		p2 = processus->reg[index];
		if ((index = set_index(corewar->memory + set_pc(pc))) < 0)
			return (return_error(processus, tab));
		processus->reg[index] = p1 + p2;
		change_carry(processus, p1 + p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
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

	pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(corewar->memory + pc++)))
	{
		if ((index = set_index(corewar->memory + pc)) < 0)
			return (return_error(processus, tab));
		pc = set_pc(pc + 1);
		p1 = processus->reg[index];
		if ((index = set_index(corewar->memory + pc++)) < 0)
			return (return_error(processus, tab));
		p2 = processus->reg[index];
		if ((index = set_index(corewar->memory + set_pc(pc))) < 0)
			return (return_error(processus, tab));
		processus->reg[index] = p1 - p2;
		change_carry(processus, p1 - p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	st1(t_corewar *corewar, t_proc *processus, int p1, unsigned int pc)
{
	int		index;

	if ((index = set_index(corewar->memory + pc)) < 0)
	{
		processus->pc = set_pc(processus->pc + 1);
		return ;
	}
	processus->reg[index] = p1;
	change_carry(processus, p1);
	processus->pc = set_pc(pc + 1);
}

void	st(t_proc *processus, t_corewar *corewar)
{
	int				p1;
	int				offset;
	int				*tab;
	unsigned int	pc;
	int				s;

	pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(corewar->memory + pc++)))
	{
		p1 = get_reg_value(processus, corewar->memory + pc++);
		if (tab[1] == 1)
			st1(corewar, processus, p1, pc);
		else if (tab[1] == 3)
		{
			offset = get_int_indirect_value(corewar->memory + pc, processus);
			s = set_pc(processus->pc + (offset % IDX_MOD));
			print_bit(corewar, s, p1);
			processus->pc = set_pc(pc + 2);
		}
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
