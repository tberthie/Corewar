/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/03 15:57:46 by ramichia         ###   ########.fr       */
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
	char	index;
	int		mv;

	if ((9 <= op && op <= 12) || op == 14 || op == 15)
		mv = 1;
	else
		mv = 3;
	index = *(char*)(corewar->memory + proc->pc + mv);
	proc->pc = (proc->pc + (mv + 1)) % MEM_SIZE;
	return ((int)index);
}

int		get_indirect_value(t_proc *processus, t_corewar *corewar)
{
	void	*adr;
	void	*tmp;
	int		value;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp++;
	adr = corewar->memory + processus->pc + (int)tmp % IDX_MOD;
	value = (int)adr;
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
