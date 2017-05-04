/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:31:07 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/04 13:53:41 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void	zjmp(t_proc *processus, t_corewar *corewar)
{
	int				tmp;
	void			*adr;
	unsigned short	val;
	short			offset;
	int				i;

	tmp = processus->pc;
	val = 0;
	i = 0;
	adr = corewar->memory + processus->pc + 1;
	while (i++ < IND_SIZE)
	{
		val |= (*(unsigned char*)adr << ((IND_SIZE - i) * 8));
		adr++;
	}
//	printf("0x%04x\n", val);
	offset = val;
//	printf("%d\n", offset);
	if (processus->carry == 1)
	{
		tmp = tmp + (offset % IDX_MOD);
		if (tmp > MEM_SIZE)
			tmp = tmp % MEM_SIZE - MEM_SIZE;
		if (tmp < 0)
			tmp = MEM_SIZE - 1 + tmp % -MEM_SIZE;
		processus->pc = (unsigned int)tmp;
	}
	else
		processus->pc += 2;
}

void	c_fork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	char			index;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc += 2;
	index = *(char*)(corewar->memory + processus->pc);
	processus2->pc = (processus->pc - 2 + (index % IDX_MOD)) % MEM_SIZE;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc++;
}

void	lfork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	char			index;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc += 2;
	index = *(char*)(corewar->memory + processus->pc);
	processus2->pc = (processus->pc + index) % MEM_SIZE;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc++;
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
