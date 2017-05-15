/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:01 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/15 18:55:18 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

int		*byte_analysis(void *adr)
{
	int		*nbr;
	unsigned char	byte;

	byte = *(unsigned char*)(adr);
	ft_print(1, "OCTET CODAGE = %d\n", byte);
	nbr = (int*)malloc(sizeof(int) * 3);
	nbr[0] = (byte >> 6) & (REG_CODE | DIR_CODE | IND_CODE);
	nbr[1] = (byte >> 4) & (REG_CODE | DIR_CODE | IND_CODE);
	nbr[2] = (byte >> 2) & (REG_CODE | DIR_CODE | IND_CODE);
	ft_print(1, "tab0=%d tab1=%d tab2=%d\n", nbr[0], nbr[1], nbr[2]);
	if ((1 <= nbr[0] && nbr[0] <= 3) && (1 <= nbr[1] && nbr[1] <= 3))
		return (nbr);
	return (NULL);
}

int		get_indirect_value(t_proc *processus, t_corewar *corewar, void *adr)
{
	void	*adr2;
	int		value;
	unsigned short		offset;
	unsigned int		tmp;
	int		i;

	i = 0;
	offset = 0;
	value = 0;
	tmp = 0;
	// adr = get_pc(processus, corewar);
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	ft_print(1, "OFFSET INDIRECT = %d\n", processus->pc + ((short)offset % IDX_MOD));
	ft_print(1, "PROCESSUS PC = %d\n", processus->pc);
	adr2 = corewar->memory + processus->pc + ((short)offset % IDX_MOD);
	ft_print(1, "1st value = %d\n", *(char*)adr2);
	i = 0;
	while (i++ < 4)
	{
		tmp |= (unsigned int)(*(unsigned char*)adr2 << ((DIR_SIZE - i) * 8));
		ft_print(1, "VALUE BOUCLE IND = %d\n", tmp);
		adr2++;
	}
	value = (int)tmp;
	// processus->pc = set_pc(processus->pc + 2);
	// ft_print(1, "VALUE INDIR : %d\n", (int)value);
	return (value);
}

int		get_indirect_value_nm(t_proc *processus, t_corewar *corewar, void *adr)
{
	void	*adr2;
	int		value;
	unsigned short		offset;
	unsigned int		tmp;
	int		i;

	i = 0;
	offset = 0;
	value = 0;
	tmp = 0;
	// adr = get_pc(processus, corewar);
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	ft_print(1, "OFFSET INDIRECT = %d\n", processus->pc + ((short)offset));

	adr2 = corewar->memory + processus->pc + ((short)offset);
	i = 0;
	while (i++ < 4)
	{
		tmp |= (unsigned int)(*(unsigned char*)adr2 << ((DIR_SIZE - i) * 8));
		ft_print(1, "VALUE BOUCLE IND = %d\n", tmp);
		adr2++;
	}
	value = (int)tmp;
	// processus->pc = set_pc(processus->pc + 2);
	// ft_print(1, "VALUE INDIR : %d\n", (int)value);
	return (value);
}

int		get_value_nm(t_proc *proc, t_corewar *cr, int nbr, unsigned char op, void *adr)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(op, adr);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value_nm(proc, cr, adr);
	else
		p1 = get_reg_value(proc, cr);
	return (p1);
}

int		set_index(void *adr)
{
	int		index;

	index = *(char*)(adr);
	if (index < 1 || 16 < index)
	{
		// processus->carry = 0;
		// change_carry(processus);
		// processus->pc = set_pc(processus->pc + 1);
		return (-1);
	}
	else
	{
		// processus->pc = set_pc(processus->pc + 1);
		return (index - 1);
	}
}

void	*get_pc(int	index, t_corewar *corewar)
{
	void	*adr;
	int		pc;

	pc = set_pc(index);
	adr = corewar->memory + pc;
	return (adr);
}

unsigned int	set_pc(int tmp)
{
	if (tmp > MEM_SIZE - 1)
		tmp = tmp % MEM_SIZE;
	if (tmp < 0)
		tmp = MEM_SIZE + tmp % -MEM_SIZE;
	// ft_print(1, "JUMP = %d\n", tmp);
	return(tmp);
}
