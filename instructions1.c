/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:21 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/05 14:22:40 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void	live(t_proc *processus, t_corewar *corewar)
{
	t_champ	*champ;

	processus->live++;
	if ((champ = get_player(corewar, processus)))
	{
		corewar->last_alive = champ->number;
		ft_printf(1, "A process says player %d(%s) is alive\n", champ->number,
		champ->name);
	}
	processus->pc += 5;
}

void	*get_pc(t_proc *processus, t_corewar *corewar)
{
	void	*adr;
	int		pc;

	pc = set_pc((int)processus->pc);
	adr = corewar->memory + pc;
	return (adr);
}

void	c_and(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_printf(1, "1 = %d\n", p1);
		p2 = get_value(processus, corewar, tab[1], op);
		// ft_printf(1, "2 = %d\n", p2);
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		// ft_printf(1, "index = %d\n", (int)index);
		*(int*)processus->reg[(int)index - 1] = p1 & p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	c_or(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	int		index;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		p2 = get_value(processus, corewar, tab[1], op);
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = p1 | p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	c_xor(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		p2 = get_value(processus, corewar, tab[1], op);
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = p1 ^ p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}
