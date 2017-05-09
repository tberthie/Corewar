/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:07 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/09 14:52:35 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"
#include <stdio.h>

unsigned int	set_pc(int tmp)
{
	if (tmp > MEM_SIZE)
		tmp = tmp % MEM_SIZE;
	if (tmp < 0)
		tmp = MEM_SIZE - 1 + tmp % -MEM_SIZE;
	// ft_printf(1, "JUMP = %d\n", tmp);
	return(tmp);
}

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
	if (processus->carry == 1)
	{
		tmp = tmp + (value % IDX_MOD);
		processus->pc = set_pc(tmp);
	}
	else
		processus->pc += 2;
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
	// ft_printf(1, "NEW PC FORK1 = %d\n", value);
	processus2->pc = (processus->pc + value);
	// ft_printf(1, "NEW PC FORK2 = %d\n", processus2->pc);
	// processus2->reg = ft_memalloc(4 * REG_NUMBER);
	ft_memcpy(processus2->reg, processus->reg, 4 * REG_NUMBER);
	// ft_printf(1, "PC2 = %d\n", processus2->pc);
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc += 3;
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
	processus2->pc = processus->pc + value % MEM_SIZE;
	// processus2->reg = ft_memalloc(4 * REG_NUMBER);
	ft_memcpy(processus2->reg, processus->reg, 4 * REG_NUMBER);
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc += 3;
}

void	aff(t_proc *processus, t_corewar *corewar)
{
	char	aff;
	int		value;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		processus->pc++;
		value = get_reg_value(processus, corewar);
		aff = value % 256;
		ft_putchar(aff);
	}
	processus->pc++;
}
