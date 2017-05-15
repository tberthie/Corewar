/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:07 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/15 19:35:11 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"
#include <stdio.h>

void	zjmp(t_proc *processus, t_corewar *corewar)
{
	int				tmp;
	void			*adr;
	unsigned short	offset;
	int				i;
	short			value;

	tmp = processus->pc;
	offset = 0;
	i = 0;
	adr = corewar->memory + processus->pc + 1;
	while (i++ < IND_SIZE)
	{
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
	offset += (0xffff << 16);
	value = (short)offset;
	// ft_print(1, "CARRY JUMP = %d\n", processus->carry);
	if (processus->carry == 1)
	{
		tmp = tmp + ((int)value % IDX_MOD);
		// ft_print(1, "JUMP = %d\n", tmp);
		processus->pc = set_pc(tmp);
		// ft_print(1, "NEW PC = %d\n", processus->pc);
	}
	else
		processus->pc = set_pc(processus->pc + 3);
}

void	c_fork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	short			value;
	void 			*adr;
	unsigned short	offset;
	int				i;

	i = 0;
	offset = 0;
	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	adr = corewar->memory + processus->pc + 1;
	while (i++ < IND_SIZE)
	{
		// printf("VALUE = %04x\n", *(unsigned char*)adr);
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		// printf("OFFSET: %d\n", offset);
		adr++;
	}
	offset += (0xffff << 16);
	value = (short)offset;
	// ft_print(1, "NEW PC FORK1 = %d\n", value);
	processus2->pc = set_pc(processus->pc + (value % IDX_MOD));
	processus2->carry = processus->carry;
	// ft_print(1, "NEW PC FORK = %d\n", processus2->pc);
	processus2->reg = ft_memalloc(4 * REG_NUMBER);
	ft_memcpy(processus2->reg, processus->reg, 4 * REG_NUMBER);
	cycles(corewar, processus2);
	if (processus->live)
		processus2->safe = 1;
	processus2->live = 0;
	// ft_print(1, "PC2 = %d\n", processus2->pc);
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc = set_pc(processus->pc + 3);
}

void	lfork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	short			value;
	void 			*adr;
	unsigned short	offset;
	int				i;

	i = 0;
	offset = 0;
	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	adr = corewar->memory + processus->pc + 1;
	while (i++ < IND_SIZE)
	{
		// printf("VALUE = %04x\n", *(unsigned char*)adr);
		offset |= (unsigned short)(*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		// printf("OFFSET: %d\n", offset);
		adr++;
	}
	offset += (0xffff << 16);
	value = (short)offset;
	// ft_print(1, "NEW PC FORK1 = %d\n", value);
	processus2->pc = set_pc(processus->pc + (value));
	processus2->carry = processus->carry;
	// ft_print(1, "NEW PC FORK = %d\n", processus2->pc);
	processus2->reg = ft_memalloc(4 * REG_NUMBER);
	ft_memcpy(processus2->reg, processus->reg, 4 * REG_NUMBER);
	cycles(corewar, processus2);
	if (processus->live)
		processus2->safe = 1;
	processus2->live = 0;
	// ft_print(1, "PC2 = %d\n", processus2->pc);
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc = set_pc(processus->pc + 3);
}

void	aff(t_proc *processus, t_corewar *corewar)
{
	char	aff;
	int		value;
	int		*tab;
	int		pc;

	pc = processus->pc + 1;
	if ((tab = byte_analysis(corewar->memory + pc)))
	{
		pc++;
		value = get_reg_value(processus, corewar->memory + pc);
		pc++;
		aff = value % 256;
		ft_putchar(aff);
		// change_carry(processus, (int)aff);
		processus->pc = set_pc(processus->pc + pc);
	}
	processus->pc = set_pc(processus->pc + 1);
}
