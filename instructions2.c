/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:33 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/12 17:20:58 by ramichia         ###   ########.fr       */
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

	processus->pc = set_pc(processus->pc + 1);
	// ft_print(1, "PC = %d\n", processus->pc);
	if ((tab = byte_analysis(processus, corewar)))
	{
		// ft_print(1, "PC2 = %d\n", processus->pc);
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_print(1, "LD VALUE = %d\n", p1);
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		// ft_print(1, "PC4 = %d\n", processus->pc);
		// ft_print(1, "INDEX = %d\n", index);
		processus->reg[index] = p1;
		change_carry(processus, p1);
	}
	else
		processus->pc = set_pc(processus->pc + 1);

}

void	lld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		index;
	int		*tab;

	processus->pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value_nm(processus, corewar, tab[0], op);
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		processus->reg[index] = p1;
		change_carry(processus, p1);
		// processus->carry = 1;
	}
	else
	{
		processus->pc = set_pc(processus->pc + 1);
		// processus->carry = 0;
	}
}

void	ldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int						*tab;
	int						index;
	int						nbr;
	int						value;
	unsigned	int tmp;

	tmp = processus->pc;
	processus->pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(processus, corewar)))
	{
		nbr = get_value(processus, corewar, tab[0], op);
		ft_print(1, "OFFSET PREVIEW LDI = %d\n", nbr);
		nbr += get_value(processus, corewar, tab[1], op);
		ft_print(1, "OFFSET TOTAL LDI = %d\n", nbr);
		value = *(unsigned int*)(corewar->memory + tmp + (nbr % IDX_MOD));
		ft_print(1, "VALUE LDI = %d\n", value);
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		processus->reg[index] = value;
		change_carry(processus, value);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	lldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int			*tab;
	int			index;
	int			nbr;
	int			value;
	unsigned	int tmp;

	tmp = processus->pc;
	processus->pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(processus, corewar)))
	{
		nbr = get_value_nm(processus, corewar, tab[0], op);
		// ft_print(1, "P1 = %d\n", p1);
		nbr += get_value_nm(processus, corewar, tab[1], op);
		// ft_print(1, "NBR = %d\n", nbr);
		nbr = set_pc(nbr + tmp);
		value = *(int*)(corewar->memory + nbr);
		if ((index = set_index(processus, corewar)) < 0)
			return ;
		processus->reg[index] = value;
		change_carry(processus, value);
		// processus->carry = 1;
	}
	else
	{
		processus->pc = set_pc(processus->pc + 1);
		// processus->carry = 0;
	}
	//processus->pc++;

}

void 	st1(t_corewar *corewar, t_proc *processus, int p1)
{
	int		index;

	if ((index = set_index(processus, corewar)) < 0)
	{
		processus->pc = set_pc(processus->pc + 1);
		return ;
	}
	processus->reg[index] = p1;
	processus->pc = set_pc(processus->pc + 1);
	// ft_print(1, "INDEX ST = %d\n", (int)index);
	// ft_print(1, "FINAL VALUE ST %d\n", *(int*)processus->reg[index - 1]);
	//processus->pc++;
}

void	st(t_proc *processus, t_corewar *corewar)
{
	int				p1;
	int				offset;
	int				*tab;
	unsigned int	tmp;
	int				S;

	tmp = processus->pc;
	processus->pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_reg_value(processus, corewar);

		ft_print(1, "P1 ST = %d\n", p1);
		if (tab[1] == 1)
			st1(corewar, processus, p1);
		else if (tab[1] == 3)
		{
			offset = get_int_indirect_value(corewar->memory + processus->pc);
			// ft_print(1, "VALUE OFFSET PREMS ST: %d\n", offset);
			S = set_pc(tmp + (offset % IDX_MOD));
			ft_print(1, "Offset ST = %d\n", S);
			print_bit(corewar->memory + S, p1);
			// ft_print(1, "FINAL VALUE ST %d\n", *(int*)(corewar->memory + S));
			processus->pc = set_pc(processus->pc + 2);
			change_carry(processus, p1);
		}
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
