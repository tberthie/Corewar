/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:07 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/23 15:07:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	zjmp(t_proc *processus, t_corewar *corewar)
{
	int				tmp;
	void			*adr;
	unsigned short	off;
	int				i;
	short			value;

	tmp = processus->pc;
	off = 0;
	i = 0;
	adr = corewar->memory + set_pc(processus->pc + 1);
	while (i++ < IND_SIZE)
	{
		off |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	off += (0xffff << 16);
	value = (short)off;
	if (processus->carry == 1)
	{
		tmp = tmp + (value % IDX_MOD);
		processus->pc = set_pc(tmp);
	}
	else
		processus->pc = set_pc(processus->pc + 3);
}

void	processus_fork(t_proc *processus, t_proc *processus2, short value, \
						unsigned char op)
{
	if (op == 12)
		processus2->pc = set_pc(processus->pc + (value % IDX_MOD));
	else
		processus2->pc = set_pc(processus->pc + value);
	processus2->carry = processus->carry;
	processus2->reg = ft_memalloc(4 * REG_NUMBER);
	processus2->live = 0;
}

void	c_fork(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	t_proc			*processus2;
	short			value;
	void			*adr;
	unsigned short	off;
	int				i;

	i = 0;
	off = 0;
	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	adr = corewar->memory + set_pc(processus->pc + 1);
	while (i++ < IND_SIZE)
	{
		off |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	off += (0xffff << 16);
	value = (short)off;
	processus_fork(processus, processus2, value, op);
	ft_memcpy(processus2->reg, processus->reg, 4 * REG_NUMBER);
	cycles(corewar, processus2);
	if (processus->live)
		processus2->safe = 1;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc = set_pc(processus->pc + 3);
}

void	lfork(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	t_proc			*processus2;
	short			value;
	void			*adr;
	unsigned short	off;
	int				i;

	i = 0;
	off = 0;
	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	adr = corewar->memory + set_pc(processus->pc + 1);
	while (i++ < IND_SIZE)
	{
		off |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	off += (0xffff << 16);
	value = (short)off;
	processus_fork(processus, processus2, value, op);
	ft_memcpy(processus2->reg, processus->reg, 4 * REG_NUMBER);
	cycles(corewar, processus2);
	if (processus->live)
		processus2->safe = 1;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc = set_pc(processus->pc + 3);
}

void	aff(t_proc *processus, t_corewar *corewar)
{
	char	aff;
	int		value;
	int		pc;

	pc = set_pc(processus->pc + 1);
	if (*(unsigned char*)(corewar->memory + pc) == 64)
	{
		pc = set_pc(pc + 1);
		value = get_reg_value(processus, corewar->memory + pc);
		pc = set_pc(pc + 1);
		aff = value % 256;
		if (corewar->visual)
			ft_strpush(&processus->champ->aff, aff);
		else
		{
			ft_print(1, "%s: says: ", processus->champ->name);
			ft_putchar(aff);
			ft_putchar('\n');
		}
		processus->pc = set_pc(pc);
	}
	else
		processus->pc = set_pc(processus->pc + 1);
}
