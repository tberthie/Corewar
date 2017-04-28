/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 19:16:20 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/28 12:46:59 by tberthie         ###   ########.fr       */
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
	printf(" - run 0x%x", op);
//	op == 1 ? live(proc, corewar) : 0;
//	op == 2 ? ld(proc, corewar) : 0;
//	op == 3 ? st(proc, corewar) : 0;
//	op == 4 ? add(proc, corewar) : 0;
//	op == 5 ? sub(proc, corewar) : 0;
//	op == 6 ? and(proc, corewar) : 0;
//	op == 7 ? or(proc, corewar) : 0;
//	op == 8 ? xor(proc, corewar) : 0;
//	op == 9 ? zjmp(proc, corewar) : 0;
//	op == 10 ? ldi(proc, corewar) : 0;
//	op == 11 ? sti(proc, corewar) : 0;
//	op == 12 ? fork(proc, corewar) : 0;
//	op == 13 ? lld(proc, corewar) : 0;
//	op == 14 ? lldi(proc, corewar) : 0;
//	op == 15 ? lfork(proc, corewar) : 0;
//	op == 16 ? aff(proc, corewar) : 0;
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
			printf("p#%d", i + 0);
			if (corewar->proc[i]->wait)
				corewar->proc[i]->wait--;
			if (!corewar->proc[i]->wait)
			{
				execute(corewar, corewar->proc[i]);
				cycles(corewar->proc[i]);
			}
			printf(" - %dc\n", corewar->proc[i]->wait);
		}
	}
}
