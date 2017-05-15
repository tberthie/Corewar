/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/15 14:53:29 by ramichia         ###   ########.fr       */
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

int		get_direct_value(unsigned char op, void *adr)
{
	int			value;
	int				mv;
	int				i;
	// void 			*adr;

	i = 0;
	value = 0;
	// adr= get_pc(proc, corewar);
	if ((9 <= op && op <= 12) || op == 14 || op == 15)
	{
		mv = 1;
		value = get_int_indirect_value(adr);
	}
	else
	{
		mv = 3;

		value = get_int_direct_value(adr);
	}
	// proc->pc = set_pc(proc->pc + mv + 1);
	// ft_print(1, "VALUE DIR : %d\n", (int)value);
	return (value);
}

int		get_reg_value(t_proc *processus, void *adr)
{
	char	index;
	unsigned int		value;
	int		index2;

	index = *(char*)(adr);
	index2 = (int)index - 1;
	// ft_print(1, "index :%d\n", index2);
	if (index2 < 0 || 15 < index2)
		return (0);
	// if (index2 == 0)
	// 	return(-1);
	value = processus->reg[index2];
	// processus->pc = set_pc(processus->pc + 1);
	return (value);
}

int		get_value(t_proc *proc, t_corewar *corewar, int nbr, unsigned char op, void *adr)
{
	int		p1;


	if (nbr == 2)
		p1 = get_direct_value(op, adr);
	else if (nbr == 3)
		p1 = get_indirect_value(proc, corewar, adr);
	else
		p1 = get_reg_value(proc, adr);
	return (p1);
}

int		move_pc(int	tab, unsigned char op)
{
	if (tab == 1)
		return (1);
	else if (tab == 2)
	{
		if ((9 <= op && op <= 12) || op == 14 || op == 15)
			return (2);
		else
			return (4);
	}
	else
		return (2);
}
