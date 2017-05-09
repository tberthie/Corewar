/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:01 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/09 12:56:24 by ramichia         ###   ########.fr       */
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

int		get_indirect_value(t_proc *processus, t_corewar *corewar)
{
	void	*adr;
	int		value;
	unsigned short		offset;
	unsigned int		tmp;
	int		i;

	i = 0;
	offset = 0;
	value = 0;
	tmp = 0;
	adr = get_pc(processus, corewar);
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	adr = corewar->memory + processus->pc + ((short)offset % IDX_MOD);
	i = 0;
	while (i++ < 4)
	{
		tmp |= (unsigned int)(*(unsigned char*)adr << ((DIR_SIZE - i) * 8));
		adr++;
	}
	value = (int)tmp;
	processus->pc = (processus->pc + 2) % MEM_SIZE;
	// ft_printf(1, "VALUE INDIR : %d\n", (int)value);
	return (value);
}

int		get_indirect_value_nm(t_proc *processus, t_corewar *corewar)
{
	void	*adr;
	int		value;
	unsigned short		offset;
	unsigned short		tmp;
	int		i;

	i = 0;
	offset = 0;
	value = 0;
	tmp = 0;
	adr = get_pc(processus, corewar);
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	adr = corewar->memory + processus->pc + ((short)offset);
	i = 0;
	while (i++ < IND_SIZE)
	{
		tmp |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	tmp += (0xffff << 16);
	value = (short)tmp;
	processus->pc = (processus->pc + 2) % MEM_SIZE;
	// ft_printf(1, "VALUE INDIR : %d\n", (int)value);
	return ((int)value);
}

int		get_value_nm(t_proc *proc, t_corewar *cr, int nbr, unsigned char op)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(proc, cr, op);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value_nm(proc, cr);
	else
		p1 = get_reg_value(proc, cr);
	return (p1);
}
