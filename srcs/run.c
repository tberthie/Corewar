/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/27 17:20:46 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static char				alive_proc(t_proc **proc)
{
	t_proc	**tmp;

	tmp = proc;
	while (*tmp)
	{
		if ((*tmp)->alive)
			return (1);
		tmp++;
	}
	return (0);
}

static unsigned int		check_live(t_proc **proc)
{
	t_proc			**tmp;
	unsigned int	total;

	total = 0;
	tmp = proc;
	while (*tmp)
	{
		if (!(*tmp)->live)
			(*tmp)->alive = 0;
		total += (*tmp)->live;
		(*tmp)->live = 0;
		tmp++;
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
			ft_printf(1, GREEN"Player %d(%s) won\n"EOC, corewar->last_alive,
			corewar->champs[i]->name);
			ft_printf(1, "Duration: %d cycles\n", corewar->cycle);
			return ;
		}
		i++;
	}
}

static void				dump(t_corewar *corewar)
{
	int			i;
	int			pad;

	pad = 32;
	i = 0;
	while (i++ < MEM_SIZE)
	{
		hex_dump(*(unsigned char*)corewar->memory++);
		if (!--pad)
		{
			ft_printf(1, "\n");
			pad = 32;
		}
		else
			ft_printf(1, " ");
	}
	if (pad)
		ft_printf(1, "\n");
	exit(0);
}

void					run(t_corewar *corewar)
{
	unsigned int	cycle;
	unsigned int	lives;
	unsigned int	i;

	cycle = 0;
	i = ft_parrlen((void**)corewar->proc);
	while (i--)
		cycles(corewar->proc[i]);
	while (alive_proc(corewar->proc))
	{
		process(corewar);
		if (++corewar->cycle == corewar->dump)
			dump(corewar);
		cycle++;
		if ((cycle >= corewar->ctd && (lives = check_live(corewar->proc)) >=
		NBR_LIVE) || !--corewar->check)
		{
			corewar->ctd -= CYCLE_DELTA > corewar->ctd ?
			corewar->ctd : CYCLE_DELTA;
			corewar->check = MAX_CHECKS;
		}
		cycle = cycle >= corewar->ctd ? 0 : cycle;
	}
	result(corewar);
}
