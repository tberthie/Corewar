/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:57:01 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/02 19:06:44 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

int		get_indirect_value_nm(t_proc *processus, t_corewar *corewar)
{
	void	*adr;
	void	*tmp;
	int		value;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp++;
	adr = corewar->memory + processus->pc + (int)tmp;
	value = (int)adr;
	processus->pc = (processus->pc + 2) % MEM_SIZE;
	return (value);
}

int		get_value_nm(t_proc *proc, t_corewar *cr, int nbr, unsigned char op)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(proc, cr, op);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value_nm(proc, cr);
	else
		p1 = get_reg_value(proc, cr);
	return (p1);
}
