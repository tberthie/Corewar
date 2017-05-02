/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:33 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/02 19:22:42 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void	ld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	char	index;
	int		*tab;

	processus->pc++;
	// ft_printf(1, "yolo\n");
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_printf(1, "P1 = %d\n", p1);
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "index :%d\n", (int)index);
		// ft_printf(1, "INDEX = %d\n", (int)index);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = p1;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	lld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		index;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value_nm(processus, corewar, tab[0], op);
		index = *(char*)(corewar->memory + processus->pc);
		*(int*)processus->reg[(int)index - 1] = p1;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	ldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		index;
	int		p1;
	int		nbr;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_printf(1, "P1 = %d\n", p1);
		nbr = p1 + get_value(processus, corewar, tab[1], op);
		// ft_printf(1, "NBR = %d\n", nbr);
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "index :%d\n", (int)index);
		if (index < 0 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = nbr;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	lldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		index;
	int		p1;
	int		nbr;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value_nm(processus, corewar, tab[0], op);
		// ft_printf(1, "P1 = %d\n", p1);
		nbr = p1 + get_value_nm(processus, corewar, tab[1], op);
		// ft_printf(1, "NBR = %d\n", nbr);
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "index :%d\n", (int)index);
		*(int*)processus->reg[(int)index - 1] = nbr;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void	st(t_proc *processus, t_corewar *corewar)
{
	int		p1;
	int		index;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_reg_value(processus, corewar);
		// ft_printf(1, "P1 = %d\n", p1);
		processus->pc++;
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "INDEX = %d\n", (int)index);
		if (tab[1] == 1)
			ft_memcpy(processus->reg[index], &p1, REG_SIZE);
		// else if (tab[1] == 10)
		// 	ft_memcpy(corewar->memory + (index % IDX_MOD), &p1, REG_SIZE);
		else if (tab[1] == 11)
			ft_memcpy(corewar->memory + processus->pc + \
				(index % IDX_MOD), &p1, REG_SIZE);
	}
	processus->pc++;
}
