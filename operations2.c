/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:01 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/16 19:05:54 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

int		get_indirect_value(t_proc *processus, t_corewar *corewar, void *adr)
{
	void			*adr2;
	unsigned short	offset;
	unsigned int	tmp;
	int				i;

	i = 0;
	offset = 0;
	tmp = 0;
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << \
				((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	adr2 = corewar->memory + processus->pc + ((short)offset % IDX_MOD);
	i = 0;
	while (i++ < 4)
	{
		tmp |= (unsigned int)(*(unsigned char*)adr2 << ((DIR_SIZE - i) * 8));
		adr2++;
	}
	return ((int)tmp);
}

int		get_indirect_value_nm(t_proc *processus, t_corewar *corewar, void *adr)
{
	void			*adr2;
	unsigned short	offset;
	unsigned int	tmp;
	int				i;

	i = 0;
	offset = 0;
	tmp = 0;
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << \
				((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	adr2 = corewar->memory + processus->pc + ((short)offset);
	i = 0;
	while (i++ < 4)
	{
		tmp |= (unsigned int)(*(unsigned char*)adr2 << ((DIR_SIZE - i) * 8));
		adr2++;
	}
	return ((int)tmp);
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

void	*get_pc(int index, t_corewar *corewar)
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
	return (tmp);
}
