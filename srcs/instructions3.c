/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:44 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/04 13:29:53 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void	sti(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		tmp;
	int		p1;
	int		p2;
	int		p3;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_reg_value(processus, corewar);
		p2 = get_value(processus, corewar, tab[1], op);
		p3 = get_value(processus, corewar, tab[2], op);
		tmp = p2 + p3;
		if (MEM_SIZE < tmp)
			tmp = tmp % MEM_SIZE - MEM_SIZE;
		if (tmp < 0)
			tmp = MEM_SIZE - 1 + tmp % -MEM_SIZE;
		ft_memcpy(corewar->memory + tmp, &p1, REG_SIZE);
	}
	processus->pc++;
}

int		set_index(t_proc *processus, t_corewar *corewar)
{
	int		index;

	index = *(char*)(corewar->memory + processus->pc);
	if (index < 2 || 15 < index)
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
