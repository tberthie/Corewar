/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/23 14:52:09 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void				remove_proc(t_corewar *corewar, t_proc *proc)
{
	ft_parrprem((void**)corewar->proc, proc);
	free(proc->reg);
	free(proc);
}

unsigned int			check_live(t_corewar *corewar)
{
	unsigned int	total;
	unsigned int	i;
	t_proc			*proc;

	total = 0;
	i = 0;
	while (i < ft_parrlen((void**)corewar->proc))
	{
		proc = corewar->proc[i];
		if (!proc->live && !proc->safe)
		{
			if (corewar->visual)
				corewar->color[proc->pc] = multi_color(proc->champ->color, 0.8);
			remove_proc(corewar, proc);
		}
		else
		{
			total += proc->live;
			proc->live = 0;
			proc->safe = 0;
			i++;
		}
	}
	return (total);
}

static void				result(t_corewar *corewar)
{
	int		i;

	i = 0;
	if (!find_champion(corewar->champs, corewar->last_alive))
		error(0, "Nobody has won the match");
	while (corewar->champs[i])
	{
		if (corewar->champs[i]->number == corewar->last_alive)
		{
			ft_print(1, GREEN"\nPlayer %d(%s) won\n"EOC, corewar->last_alive,
			corewar->champs[i]->name);
			ft_print(1, "Duration: %d cycles\n", corewar->cycle);
			return ;
		}
		i++;
	}
}

void					dump(t_corewar *corewar)
{
	unsigned int	i;
	int				pad;

	pad = 32;
	i = 0;
	ft_printf("\n0x%0*x : ", 4, i);
	while (i < MEM_SIZE)
	{
		hex_dump(((unsigned char*)corewar->memory)[i++]);
		if (!--pad && i != MEM_SIZE)
		{
			ft_printf("\n0x%0*x : ", 4, i);
			pad = 32;
		}
		else
			ft_print(1, " ");
	}
	if (!pad)
		ft_print(1, "\n");
	!corewar->visual ? exit(0) : 0;
}

void					run(t_corewar *corewar)
{
	unsigned int	cycle;

	cycle = 0;
	while (ft_parrlen((void**)corewar->proc))
	{
		process(corewar);
		if (++corewar->cycle == corewar->dump)
			dump(corewar);
		if (++cycle >= corewar->ctd && (check_live(corewar)
		>= NBR_LIVE || corewar->check <= 0))
		{
			corewar->ctd -= CYCLE_DELTA > corewar->ctd ?
			corewar->ctd : CYCLE_DELTA;
			corewar->check = MAX_CHECKS;
		}
		else
			--corewar->check;
		cycle = cycle >= corewar->ctd ? 0 : cycle;
	}
	corewar->dump ? dump(corewar) : result(corewar);
}
