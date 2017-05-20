/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:21 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/20 13:22:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void	live(t_proc *processus, t_corewar *corewar)
{
	t_champ	*champ;

	processus->live++;
	champ = processus->champ;
	corewar->last_alive = champ->number;
	if (!corewar->visual)
		ft_print(1, "A process says player %d(%s) is alive\n",
		champ->number, champ->name);
	processus->pc = set_pc(processus->pc + 5);
}

void	c_and(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		p1 = get_value(processus, tab[0], op, corewar->memory + pc);
		pc += move_pc(tab[0], op);
		p2 = get_value(processus, tab[1], op, corewar->memory + pc);
		pc += move_pc(tab[1], op);
		if ((index = set_index(corewar->memory + pc)) < 0)
			return (return_error(processus, tab));
		processus->reg[(int)index - 1] = p1 & p2;
		change_carry(processus, p1 & p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	c_or(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		p1 = get_value(processus, tab[0], op, corewar->memory + pc);
		pc += move_pc(tab[0], op);
		p2 = get_value(processus, tab[1], op, corewar->memory + pc);
		pc += move_pc(tab[1], op);
		if ((index = set_index(corewar->memory + pc)) < 0)
			return (return_error(processus, tab));
		processus->reg[(int)index - 1] = p1 | p2;
		change_carry(processus, p1 | p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}

void	c_xor(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		p1 = get_value(processus, tab[0], op, corewar->memory + pc);
		pc += move_pc(tab[0], op);
		p2 = get_value(processus, tab[1], op, corewar->memory + pc);
		pc += move_pc(tab[1], op);
		if ((index = set_index(corewar->memory + pc)) < 0)
			return (return_error(processus, tab));
		processus->reg[(int)index - 1] = p1 ^ p2;
		change_carry(processus, p1 ^ p2);
		processus->pc = set_pc(pc + 1);
		free(tab);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
