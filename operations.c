/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/03 17:25:38 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

int		*byte_analysis(t_proc *processus, t_corewar *corewar)
{
	int		*nbr;
	char	byte;

	byte = *(char*)(corewar->memory + processus->pc);
	nbr = (int*)malloc(sizeof(int) * 3);
	nbr[0] = (byte >> 6) & (REG_CODE | DIR_CODE | IND_CODE);
	nbr[1] = (byte >> 4) & (REG_CODE | DIR_CODE | IND_CODE);
	nbr[2] = (byte >> 2) & (REG_CODE | DIR_CODE | IND_CODE);
	processus->pc = (processus->pc + 1) % MEM_SIZE;
	if ((1 <= nbr[0] && nbr[0] <= 3) && (1 <= nbr[1] && nbr[1] <= 3))
		return (nbr);
	return (NULL);
}

int		get_direct_value(t_proc *proc, t_corewar *corewar, unsigned char op)
{
	int		value;
	int		mv;
	int		i;
	void 	*tmp;

	i = 0;
	value = 0;
	tmp = get_pc(proc, corewar);
	if ((9 <= op && op <= 12) || op == 14 || op == 15)
		mv = 1;
	else
		mv = 3;
	while (i <= mv)
	{
		value = value + (*(char*)tmp << (i * 8));
		tmp++;
		i++;
	}
	proc->pc = (proc->pc + (mv + 1)) % MEM_SIZE;
	return (value);
}

int		get_indirect_value(t_proc *processus, t_corewar *corewar)
{
	void	*adr;
	int		value;
	int		offset;
	int		i;

	i = 0;
	offset = 0;
	value = 0;
	adr = get_pc(processus, corewar);
	while (i++ < IND_SIZE)
	{
		offset = offset + (*(char*)adr << ((i - 1) * 8));
		adr++;
	}
	adr = corewar->memory + processus->pc + offset % IDX_MOD;
	i = 0;
	while (i++ < IND_SIZE)
	{
		value = value + (*(char*)adr << ((i - 1) * 8));
		adr++;
	}
	processus->pc = (processus->pc + 2) % MEM_SIZE;
	return (value);
}

int		get_reg_value(t_proc *processus, t_corewar *corewar)
{
	char	index;
	int		value;
	int		index2;

	index = *(char*)(corewar->memory + processus->pc);
	index2 = (int)index - 1;
	if (index2 < 0 || 15 < index2)
		return (0);
	value = *(int*)processus->reg[index2];
	processus->pc++;
	return (value);
}

int		get_value(t_proc *proc, t_corewar *corewar, int nbr, unsigned char op)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(proc, corewar, op);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value(proc, corewar);
	else
		p1 = get_reg_value(proc, corewar);
	return (p1);
}
