/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:33 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/24 16:29:19 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	ld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		index;
	int		*tab;
	void	*adr;
	int		pc;

	pc = set_pc(processus->pc + 1);
	adr = get_pc(pc, corewar);
	if ((tab = byte_analysis(adr)))
	{
		pc = set_pc(pc + 1);
		adr = get_pc(pc, corewar);
		p1 = get_value(processus, tab[0], op, adr);
		pc = set_pc(pc + move_pc(tab[0], op));
		adr = get_pc(pc, corewar);
		if ((index = set_index(adr)) < 0)
			return (return_error(processus, tab));
		processus->reg[index] = p1;
		change_carry(processus, p1);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	lld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		index;
	int		*tab;
	void	*adr;
	int		pc;

	pc = set_pc(processus->pc + 1);
	adr = get_pc(pc, corewar);
	if ((tab = byte_analysis(adr)))
	{
		pc = set_pc(pc + 1);
		adr = get_pc(pc, corewar);
		p1 = get_value_nm(processus, tab[0], op, adr);
		pc = set_pc(pc + move_pc(tab[0], op));
		adr = get_pc(pc, corewar);
		if ((index = set_index(adr)) < 0)
			return (return_error(processus, tab));
		processus->reg[index] = p1;
		change_carry(processus, p1);
		processus->pc = set_pc(pc + 1);
		free(tab);
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

	pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc += 1;
		nbr = get_value(processus, tab[0], op, corewar->memory + pc);
		pc = set_pc(pc + move_pc(tab[0], op));
		nbr += get_value(processus, tab[1], op, corewar->memory + pc);
		value = *(unsigned int*)(corewar->memory + processus->pc + \
				(nbr % IDX_MOD));
		pc = set_pc(pc + move_pc(tab[1], op));
		if ((index = set_index(corewar->memory + pc)) < 0)
			return (return_error(processus, tab));
		processus->reg[index] = value;
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	lldi(t_proc *processus, t_corewar *cor, unsigned char op)
{
	int						*tab;
	int						index;
	int						nbr;
	int						value;
	int						pc;

	pc = set_pc(processus->pc + 1);
	if ((tab = byte_analysis(cor->memory + pc)))
	{
		pc += 1;
		nbr = get_value_nm(processus, tab[0], op, cor->memory + pc);
		pc += move_pc(tab[0], op);
		nbr += get_value_nm(processus, tab[1], op, cor->memory + pc);
		value = *(unsigned int*)(cor->memory + set_pc(processus->pc + nbr));
		pc += move_pc(tab[1], op);
		if ((index = set_index(cor->memory + pc)) < 0)
			return (return_error(processus, tab));
		processus->reg[index] = value;
		change_carry(processus, value);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	print_bit(t_corewar *corewar, int pc, int p1)
{
	char			tab[4];
	int				i;
	int				rev;

	rev = p1;
	ft_memcpy(tab, &rev, sizeof(int));
	i = 4;
	while (0 <= --i)
	{
		pc = set_pc(pc);
		*(unsigned char*)(corewar->memory + pc) = tab[i];
		pc++;
	}
}
