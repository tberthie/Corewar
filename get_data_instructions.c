/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:00:50 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/02 18:43:22 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// proteger toutes les zones memoires si l octet de codage renvoie qqch de non coherent
#include "../includes/corewar.h"
#include "../libft/libft.h"

void     live(t_proc *processus, t_corewar *corewar)
{
    t_champ    *champ;

    processus->live++;
    if ((champ = get_player(corewar, processus)))
    {
        corewar->last_alive = champ->number;
        ft_printf(1, "A process says player %d(%s) is alive\n", champ->number,
        champ->name);
    }
	processus->pc+= 5;
}

void 	*get_pc(t_proc *processus, t_corewar *corewar)
{
	void 	*adr;

	if (MEM_SIZE < processus->pc || (int)processus->pc < 0)
		processus->pc = processus->pc % MEM_SIZE;
	adr = corewar->memory + processus->pc;
	return(adr);
}

void 	c_and(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_printf(1, "1 = %d\n", p1);
		p2 = get_value(processus, corewar, tab[1], op);
		// ft_printf(1, "2 = %d\n", p2);
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		// ft_printf(1, "index = %d\n", (int)index);
		*(int*)processus->reg[(int)index - 1] =  p1 & p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	c_or(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	int		index;;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		p2 = get_value(processus, corewar, tab[1], op);
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = p1 | p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	c_xor(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int		p2;
	int		*tab;
	char	index;;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		p2 = get_value(processus, corewar, tab[1], op);
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = p1 ^ p2;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	ld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	char 	index;
	int		*tab;

	processus->pc++;
	// ft_printf(1, "yolo\n");
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_printf(1, "P1 = %d\n", p1);
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "index :%d\n", (int)index);
		// ft_printf(1, "INDEX = %d\n", (int)index);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = p1;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	lld(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		p1;
	int 	index;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value_nm(processus, corewar, tab[0], op);
		index = *(char*)(corewar->memory + processus->pc);
		*(int*)processus->reg[(int)index - 1] = p1;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	ldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		index;
	int		p1;
	int 	nbr;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value(processus, corewar, tab[0], op);
		// ft_printf(1, "P1 = %d\n", p1);
		nbr = p1 + get_value(processus, corewar, tab[1], op);
		// ft_printf(1, "NBR = %d\n", nbr);
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "index :%d\n", (int)index);
		if (index < 0 || 15 < index)
			return ;
		*(int*)processus->reg[(int)index - 1] = nbr;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc ++;
}

void 	lldi(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int		index;
	int		p1;
	int 	nbr;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_value_nm(processus, corewar, tab[0], op);
		// ft_printf(1, "P1 = %d\n", p1);
		nbr = p1 + get_value_nm(processus, corewar, tab[1], op);
		// ft_printf(1, "NBR = %d\n", nbr);
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "index :%d\n", (int)index);
		*(int*)processus->reg[(int)index - 1] = nbr;
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc ++;
}

void 	st(t_proc *processus, t_corewar *corewar)
{
	int		p1;
	int		index;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_reg_value(processus, corewar);
		// ft_printf(1, "P1 = %d\n", p1);
		processus->pc++;
		index = *(char*)(corewar->memory + processus->pc);
		// ft_printf(1, "INDEX = %d\n", (int)index);
		if (tab[1] == 1)
			ft_memcpy(processus->reg[index], &p1, REG_SIZE);
		// else if (tab[1] == 10)
		// 	ft_memcpy(corewar->memory + (index % IDX_MOD), &p1, REG_SIZE);
		else if (tab[1] == 11)
			ft_memcpy(corewar->memory + processus->pc + (index % IDX_MOD), &p1, REG_SIZE);
	}
	processus->pc++;
}

void 	sti(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int		*tab;
	int 	tmp;
	int		p1;
	int		p2;
	int		p3;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		p1 = get_reg_value(processus, corewar);
		p2 = get_value(processus, corewar, tab[1], op);
		p3 = get_value(processus, corewar, tab[2], op);
		tmp = p2 + p3;
		if (MEM_SIZE < tmp)
			tmp = tmp % MEM_SIZE - MEM_SIZE;
		if (tmp < 0)
			tmp = MEM_SIZE - 1 + tmp % -MEM_SIZE;
		ft_memcpy(corewar->memory + tmp, &p1, REG_SIZE);
	}
	processus->pc++;
}

void 	add(t_proc *processus, t_corewar *corewar)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{

		if ((index = *(char*)(corewar->memory + processus->pc) < 0))
		{
			processus->carry = 0;
			processus->pc++;
			return ;
		}
		// ft_printf(1, "index = %d\n", (int)index);
		p1 = *(int*)processus->reg[index];
		// ft_printf(1, "p1 = %d\n", p1);
		processus->pc++;
		index = *(char*)(corewar->memory + processus->pc);
		p2 = *(int*)processus->reg[index];
		processus->pc++;
		index = *(char*)(corewar->memory + processus->pc);
		if (index < 2 || 15 < index)
			return ;
		*(int*)processus->reg[index] = (p1 + p2);
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	sub(t_proc *processus, t_corewar *corewar)
{
	int		index;
	int		p1;
	int		p2;
	int		*tab;

	processus->pc++;
	if ((tab = byte_analysis(processus, corewar)))
	{
		index = *(char*)(corewar->memory + processus->pc);
		p1 = *(int*)processus->reg[index];
		processus->pc++;
		index = *(char*)(corewar->memory + processus->pc);
		p2 = *(int*)processus->reg[index];
		processus->pc++;
		index = *(char*)(corewar->memory + processus->pc);
		*(int*)processus->reg[index] = (p1 - p2);
		processus->carry = 1;
	}
	else
		processus->carry = 0;
	processus->pc++;
}

void 	zjmp(t_proc *processus, t_corewar *corewar, unsigned char op)
{
	int 	p1;

	processus->pc++;
	p1 = get_value(processus, corewar, DIR_CODE, op);
	// ft_printf(1, "JUMP = %d\n", p1);
	if (processus->carry == 1)
	{
		processus->pc = (processus->pc + (p1 % IDX_MOD));
		if (processus->pc > MEM_SIZE)
      		processus->pc = processus->pc % MEM_SIZE - MEM_SIZE;
	  	if ((int)processus->pc < 0)
			processus->pc = MEM_SIZE - 1 + processus->pc % -MEM_SIZE;
	}
	processus->pc++;

}

void 	c_fork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	char			index;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc+=2;
	index = *(char*)(corewar->memory + processus->pc);
	processus2->pc = (processus->pc + (index % IDX_MOD)) % MEM_SIZE;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc++;
}

void 	lfork(t_proc *processus, t_corewar *corewar)
{
	t_proc			*processus2;
	char			index;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc+=2;
	index = *(char*)(corewar->memory + processus->pc);
	processus2->pc = (processus->pc + index) % MEM_SIZE;
	ft_parrpush((void***)&corewar->proc, processus2);
	processus->pc++;
}

void 	aff(t_proc *processus, t_corewar *corewar)
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
