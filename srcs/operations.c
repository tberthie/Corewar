/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/20 14:38:52 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

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
	return (value);
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
		adr++;
	}
	tmp += (0xffff << 16);
	tmp2 = (short)tmp;
	value = (int)tmp2;
	return (value);
}

int		get_direct_value(unsigned char op, void *adr)
{
	int				value;
	int				i;

	i = 0;
	value = 0;
	if ((9 <= op && op <= 12) || op == 14 || op == 15)
		value = get_int_indirect_value(adr);
	else
		value = get_int_direct_value(adr);
	return (value);
}

int		get_reg_value(t_proc *processus, void *adr)
{
	char			index;
	unsigned int	value;
	int				index2;

	index = *(char*)(adr);
	index2 = (int)index - 1;
	if (index2 < 0 || 15 < index2)
	{
		processus->pc = set_pc(processus->pc + 1);
		return (0);
	}
	value = processus->reg[index2];
	return (value);
}

int		get_value(t_proc *proc, int nbr, unsigned char op, void *adr)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(op, adr);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value(proc, adr);
	else
		p1 = get_reg_value(proc, adr);
	return (p1);
}
