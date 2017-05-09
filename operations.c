/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/09 18:23:37 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"
#include <stdio.h>

int		get_int_direct_value(void *adr)
{
	unsigned int	tmp;
	int				value;
	int				i;

	i = 0;
	tmp = 0;
	value = 0;
	while (i++ < 4)
	{
		tmp |= (unsigned int)(*(unsigned char*)adr << ((DIR_SIZE - i) * 8));
		adr++;
	}
	value = (int)tmp;
	return(value);
}

int		get_int_indirect_value(void *adr)
{
	unsigned short	tmp;
	short			tmp2;
	int				value;
	int				i;

	i = 0;
	tmp = 0;
	value = 0;
	while (i++ < 2)
	{
		tmp |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		// printf("TMP STI = %02x\n", tmp);
		adr++;
	}
	tmp += (0xffff << 16);
	tmp2 = (short)tmp;
	// printf("TMP SHORT STI = %02x %d\n", tmp2, tmp2);
	value = (int)tmp2;
	// printf("TMP INT STI = %02x %d\n", value, value);
	return(value);
}

int		get_direct_value(t_proc *proc, t_corewar *corewar, unsigned char op)
{
	int			value;
	int				mv;
	int				i;
	void 			*adr;

	i = 0;
	value = 0;
	adr= get_pc(proc, corewar);
	if ((9 <= op && op <= 12) || op == 14 || op == 15)
	{
		mv = 1;
		value = get_int_indirect_value(adr);
	}
	else
	{
		mv = 3;
		ft_printf(1, "MV = %d\n", mv);
		value = get_int_direct_value(adr);
	}
	proc->pc = (proc->pc + (mv + 1)) % MEM_SIZE;
	// ft_printf(1, "VALUE DIR : %d\n", (int)value);
	return (value);
}

int		get_reg_value(t_proc *processus, t_corewar *corewar)
{
	char	index;
	unsigned int		value;
	int		index2;

	index = *(char*)(corewar->memory + processus->pc);
	index2 = (int)index - 1;
	// ft_printf(1, "index :%d\n", index2);
	if (index2 < 0 || 15 < index2)
		return (0);
	value = processus->reg[index2];
	ft_printf(1, "REG VALUE :%d\n", value);
	processus->pc++;
	return (value);
}

int		get_value(t_proc *proc, t_corewar *corewar, int nbr, unsigned char op)
{
	int		p1;

	if (nbr == 2)
		p1 = get_direct_value(proc, corewar, op);
	else if (nbr == 3)
		p1 = get_indirect_value(proc, corewar);
	else
		p1 = get_reg_value(proc, corewar);
	return (p1);
}
