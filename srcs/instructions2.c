/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:33 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/15 14:53:51 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void 	change_carry(t_proc *processus, int p1)
{
	if (p1 == 0)
		processus->carry = 1;
	else
		processus->carry = 0;
}

void	ld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		index;
	int		*tab;
	void 	*adr;
	int		pc;

	pc = processus->pc + 1;
	adr = get_pc(pc, corewar);
	if ((tab = byte_analysis(adr)))
	{
		pc += 1;
		adr = get_pc(pc, corewar);
		p1 = get_value(processus, corewar, tab[0], op, adr);
		pc += move_pc(tab[0], op);
		adr = get_pc(pc, corewar);
		// ft_print(1, "LD VALUE = %d\n", p1);
		if ((index = set_index(adr)) < 0)
		{
			processus->pc++;
			return ;
		}

		// ft_print(1, "LD REG = %d\n", index + 1);
		processus->reg[index] = p1;
		change_carry(processus, p1);
		ft_print(1, "%d %d \n", processus->pc, pc);
		processus->pc = set_pc(pc + 1);
		ft_print(1, "PROC PC FIN DE LD = %d\n", processus->pc);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	lld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		index;
	int		*tab;
	void 	*adr;
	int		pc;

	pc = processus->pc + 1;
	adr = get_pc(pc, corewar);
	if ((tab = byte_analysis(adr)))
	{
		pc += 1;
		adr = get_pc(pc, corewar);
		p1 = get_value_nm(processus, corewar, tab[0], op, adr);
		pc += move_pc(tab[0], op);
		adr = get_pc(pc, corewar);
		// ft_print(1, "LD VALUE = %d\n", p1);
		if ((index = set_index(adr)) < 0)
			return ;
		// ft_print(1, "LD REG = %d\n", index + 1);
		processus->reg[index] = p1;
		change_carry(processus, p1);
		processus->pc = set_pc(pc + 1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	ldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int						*tab;
	int						index;
	int						nbr;
	int						value;
	int						pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc += 1;
		nbr = get_value(processus, corewar, tab[0], op, corewar->memory + pc);
		// ft_print(1, "OFFSET PREVIEW LDI = %d\n", nbr);
		pc +=  move_pc(tab[0], op);
		nbr += get_value(processus, corewar, tab[1], op, corewar->memory + pc);
		// ft_print(1, "OFFSET TOTAL LDI = %d\n", nbr);
		value = *(unsigned int*)(corewar->memory + processus->pc + (nbr % IDX_MOD));
		pc += move_pc(tab[1], op);
		// ft_print(1, "VALUE LDI = %d\n", value);
		if ((index = set_index(corewar->memory + pc)) < 0)
			return ;
		processus->reg[index] = value;
		change_carry(processus, value);
		processus->pc = set_pc(pc + 1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	lldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int						*tab;
	int						index;
	int						nbr;
	int						value;
	int						pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc += 1;
		nbr = get_value_nm(processus, corewar, tab[0], op, corewar->memory + pc);
		// ft_print(1, "OFFSET PREVIEW LDI = %d\n", nbr);
		pc += move_pc(tab[0], op);
		nbr += get_value_nm(processus, corewar, tab[1], op, corewar->memory + pc);
		// ft_print(1, "OFFSET TOTAL LDI = %d\n", nbr);
		value = *(unsigned int*)(corewar->memory + processus->pc + (nbr % IDX_MOD));
		pc += move_pc(tab[1], op);
		// ft_print(1, "VALUE LDI = %d\n", value);
		if ((index = set_index(corewar->memory + pc)) < 0)
		{
			processus->pc = set_pc(processus->pc + 1);
			return ;
		}

		processus->reg[index] = value;
		change_carry(processus, value);
		processus->pc = set_pc(pc + 1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void 	st1(t_corewar *corewar, t_proc *processus, int p1, unsigned int pc)
{
	int		index;

	if ((index = set_index(corewar->memory + pc)) < 0)
		return ;

	processus->reg[index] = p1;
	// ft_print(1, "INDEX ST = %d\n", (int)index);
	// ft_print(1, "FINAL VALUE ST %d\n", *(int*)processus->reg[index - 1]);
	//processus->pc++;
}

void	st(t_proc *processus, t_corewar *corewar)
{
	int				p1;
	int				offset;
	int				*tab;
	unsigned int	pc;
	int				S;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc += 1;
		p1 = get_reg_value(processus, corewar->memory + pc);
		pc += 1;
		// ft_print(1, "P1 ST = %d\n", p1);
		if (tab[1] == 1)
			st1(corewar, processus, p1, pc);
		else if (tab[1] == 3)
		{
			offset = get_int_indirect_value(corewar->memory + pc);
			// ft_print(1, "VALUE OFFSET PREMS ST: %d\n", offset);
			S = set_pc(processus->pc + (offset % IDX_MOD));
			// ft_print(1, "Offset ST = %d\n", S);
			print_bit(corewar->memory + S, p1);
			// ft_print(1, "FINAL VALUE ST %d\n", *(int*)(corewar->memory + S));
			processus->pc = set_pc(pc + 2);
			change_carry(processus, p1);
		}
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
