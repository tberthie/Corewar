/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:07 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/02 19:49:23 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void	zjmp(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;

	processus->pc++;
	p1 = get_value(processus, corewar, DIR_CODE, op);
	if (processus->carry == 1)
	{
		processus->pc = (processus->pc + (p1 % IDX_MOD));
		if (processus->pc > MEM_SIZE)
			processus->pc = processus->pc % MEM_SIZE - MEM_SIZE;
		if ((int)processus->pc < 0)
			processus->pc = MEM_SIZE - 1 + processus->pc % -MEM_SIZE;
	}
	processus->pc++;
}

void	c_fork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	char			index;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc += 2;
	index = *(char*)(corewar->memory + processus->pc);
	processus2->pc = (processus->pc + (index % IDX_MOD)) % MEM_SIZE;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc++;
}

void	lfork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	char			index;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc += 2;
	index = *(char*)(corewar->memory + processus->pc);
	processus2->pc = (processus->pc + index) % MEM_SIZE;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc++;
}

void	aff(t_proc *processus, t_corewar *corewar)
{
	char	aff;
	int		value;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		processus->pc++;
		value = get_reg_value(processus, corewar);
		aff = value % 256;
		ft_putchar(aff);
	}
	processus->pc++;
}
