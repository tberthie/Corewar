/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/05 00:23:54 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

char					alive_proc(t_proc **proc)
{
	while (*proc)
	{
		if ((*proc)->alive)
			return (1);
		proc++;
	}
	return (0);
}

unsigned int			check_live(t_corewar *corewar, t_proc **proc)
{
	unsigned int	total;
	t_champ			*player;

	total = 0;
	while (*proc)
	{
		if ((*proc)->alive && !(*proc)->live)
		{
			(*proc)->alive = 0;
			if (corewar && (player = get_player(corewar, *proc)))
				corewar->color[(*proc)->pc] = player->color;
		}
		total += (*proc)->live;
		(*proc)->live = 0;
		proc++;
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

	cycle = 0;
	while (alive_proc(corewar->proc))
	{
		process(corewar);
		if (++corewar->cycle == corewar->dump)
			dump(corewar);
		if (++cycle >= corewar->ctd && (check_live(corewar, corewar->proc)
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
	result(corewar);
}
