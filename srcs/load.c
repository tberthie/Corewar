/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:27:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/07 15:17:08 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static void		init_proc(t_proc *proc, unsigned int n, unsigned int offset)
{
	int		i;
	void	*reg;

	proc->reg = ft_parrnew();
	i = 0;
	while (i++ < REG_NUMBER)
	{
		reg = ft_memalloc(REG_SIZE);
		ft_parrpush((void***)&proc->reg, reg);
	}
	*(unsigned int*)*proc->reg = n;
	proc->carry = 1;
	proc->pc = offset;
	proc->alive = 1;
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
	init_proc(proc, corewar->champs[i]->number, (start - corewar->memory));
	cycles(corewar, proc);
	ft_parrpush((void***)&corewar->proc, proc);
}

void			load(t_corewar *corewar)
{
	t_champ			**champs;
	unsigned int	count;
	unsigned int	i;
	unsigned int	n;

	count = 0;
	n = 1;
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
		n++;
	}
}