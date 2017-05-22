/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 19:16:20 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/22 17:48:57 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		trail(t_corewar *corewar, t_proc *proc, int tmp)
{
	if (proc->pc > tmp && proc->pc - tmp < TRAIL_SIZE)
	{
		while (tmp < proc->pc)
		{
			corewar->color[tmp] = multi_color(proc->champ->color,
			(((unsigned char*)corewar->memory)[tmp] ? 0.7 : 0.6));
			tmp++;
		}
	}
}

static void		exec_op(t_proc *proc, t_corewar *corewar, unsigned char op)
{
	op == 1 ? live(proc, corewar) : 0;
	op == 2 ? ld(proc, corewar, op) : 0;
	op == 3 ? st(proc, corewar) : 0;
	op == 4 ? add(proc, corewar) : 0;
	op == 5 ? sub(proc, corewar) : 0;
	op == 6 ? c_and(proc, corewar, op) : 0;
	op == 7 ? c_or(proc, corewar, op) : 0;
	op == 8 ? c_xor(proc, corewar, op) : 0;
	op == 9 ? zjmp(proc, corewar) : 0;
	op == 10 ? ldi(proc, corewar, op) : 0;
	op == 11 ? sti(proc, corewar, op) : 0;
	op == 12 ? c_fork(proc, corewar, op) : 0;
	op == 13 ? lld(proc, corewar, op) : 0;
	op == 14 ? lldi(proc, corewar, op) : 0;
	op == 15 ? lfork(proc, corewar, op) : 0;
	op == 16 ? aff(proc, corewar) : 0;
}

static void		execute(t_corewar *corewar, t_proc *proc)
{
	int					tmp;
	unsigned char		op;

	op = ((unsigned char*)corewar->memory)[proc->pc];
	if (corewar->visual)
		corewar->color[proc->pc] = multi_color(proc->champ->color, op ?
		0.8 : 0.5);
	if ((!op || op > 16) && (proc->pc += 1) == MEM_SIZE)
		proc->pc = 0;
	tmp = proc->pc;
	exec_op(proc, corewar, op);
	if (corewar->visual)
		trail(corewar, proc, ++tmp);
}

void			cycles(t_corewar *corewar, t_proc *proc)
{
	unsigned char		op;

	op = ((unsigned char*)corewar->memory)[proc->pc];
	proc->wait = 1 + 9 * (op == 1 || op == 4 || op == 5 || op == 13) + 4 *
	(op == 2 || op == 3) + 5 * (op == 6 || op == 7 || op == 8) + 19 *
	(op == 9) + 24 * (op == 10 || op == 11) + 799 * (op == 12) + 49 *
	(op == 14) + 999 * (op == 15) + (op == 16);
}

void			process(t_corewar *corewar)
{
	unsigned int	i;

	i = ft_parrlen((void**)corewar->proc);
	while (i--)
	{
		if (corewar->proc[i]->wait)
			corewar->proc[i]->wait--;
		if (!corewar->proc[i]->wait)
		{
			execute(corewar, corewar->proc[i]);
			cycles(corewar, corewar->proc[i]);
		}
	}
}
