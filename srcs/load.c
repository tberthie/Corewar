/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:27:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/18 13:44:51 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		init_proc(t_proc *proc, t_champ *champ, unsigned int offset)
{
	proc->reg = ft_memalloc(4 * REG_NUMBER);
	proc->reg[0] = (unsigned int)champ->number;
	proc->champ = champ;
	proc->pc = offset;
}

static void		load_champion(t_corewar *corewar, unsigned int i,
				unsigned int n)
{
	void			*start;
	t_proc			*proc;

	start = corewar->memory + n * (MEM_SIZE /
	ft_parrlen((void**)corewar->champs));
	ft_memcpy(start, corewar->champs[i]->content, corewar->champs[i]->size);
	proc = ft_memalloc(sizeof(t_proc));
	init_proc(proc, corewar->champs[i], (start - corewar->memory));
	cycles(corewar, proc);
	proc->corewar = corewar;
	ft_parrpush((void***)&corewar->proc, proc);
}

void			load(t_corewar *corewar)
{
	t_champ			**champs;
	unsigned int	count;
	unsigned int	i;
	int				n;

	count = 0;
	n = -1;
	champs = corewar->champs;
	while (ft_parrlen((void**)corewar->proc) !=
	ft_parrlen((void**)corewar->champs))
	{
		i = 0;
		while (champs[i])
		{
			if (champs[i]->number == n)
				load_champion(corewar, i, count++);
			i++;
		}
		n--;
	}
}
