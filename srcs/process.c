/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 19:16:20 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/27 16:55:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void			execute(t_corewar *corewar, t_proc *proc)
{
	unsigned char		op;

	op = *(unsigned char*)proc->pc;
	if (!op || op > 16)
	{
		if (++proc->pc == corewar->memory + MEM_SIZE)
			proc->pc = corewar->memory;
	}
/*	op == 1 ? live() : 0;
	op == 2 ? ld() : 0;
	op == 3 ? st() : 0;
	op == 4 ? add() : 0;
	op == 5 ? sub() : 0;
	op == 6 ? and() : 0;
	op == 7 ? or() : 0;
	op == 8 ? xor() : 0;
	op == 9 ? zjmp() : 0;
	op == 10 ? ldi() : 0;
	op == 11 ? sti() : 0;
	op == 12 ? fork() : 0;
	op == 13 ? lld() : 0;
	op == 14 ? lldi() : 0;
	op == 15 ? lfork() : 0;
	op == 16 ? aff() : 0;*/
}

void				cycles(t_proc *proc)
{
	unsigned char		op;

	op = *(unsigned char*)proc->pc;
	proc->wait = 1 + 9 * (op == 1 || op == 4 || op == 5 || op == 13) + 4 *
	(op == 2 || op == 3) + 5 * (op == 6 || op == 7 || op == 8) + 19 *
	(op == 9) + 24 * (op == 10 || op == 11) + 799 * (op == 12) + 49 *
	(op == 14) + 999 * (op == 15) + (op == 16);
}

void				process(t_corewar *corewar)
{
	unsigned int	i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
	{
		if (corewar->proc[i]->alive)
		{
			if (corewar->proc[i]->wait)
				corewar->proc[i]->wait--;
			if (!corewar->proc[i]->wait)
			{
				execute(corewar, corewar->proc[i]);
				cycles(corewar->proc[i]);
			}
		}
	}
}
