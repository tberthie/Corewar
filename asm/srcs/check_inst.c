/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:49:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/20 13:28:12 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		check_reg(char *inst)
{
	if (inst[0] != 'r')
		return (0);
	else if (inst[0] == 'r' && (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)) ||
				ft_atoi(inst + 1) > REG_NUMBER || !ft_atoi(inst + 1)))
		return (0);
	return (1);
}

int		check_dirlabel_lastpos(t_asm *vasm, char *inst)
{
	if (inst[0] == DIRECT_CHAR && inst[1] != LABEL_CHAR &&
			!ft_strichr_cnt(inst + 1, SEPARATOR_CHAR))
	{
		if (vasm->command >= 13 && vasm->command <= 15)
		{
			if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)) && (inst[1] == '-'
				&& !ft_nisdigit(inst + 2, ft_strlen(inst + 2))) &&
				(ft_atoi(inst + 1) > MEM_SIZE || ft_atoi(inst + 1) < -MEM_SIZE))
				return (0);
		}
		else
		{
			if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)) && (inst[1] == '-'
				&& !ft_nisdigit(inst + 2, ft_strlen(inst + 2))) &&
				(ft_atoi(inst + 1) > IDX_MOD || ft_atoi(inst + 1) < -IDX_MOD))
				return (0);
		}
	}
	return (1);
}

int		check_dirlabel(t_asm *vasm, char *inst)
{
	if (inst[0] == DIRECT_CHAR && inst[1] != LABEL_CHAR)
	{
		if (vasm->command >= 13 && vasm->command <= 15)
		{
			if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)) && (inst[1] == '-'
				&& !ft_nisdigit(inst + 2, ft_strlen(inst + 2))) &&
				(ft_atoi(inst + 1) > MEM_SIZE || ft_atoi(inst + 1) < -MEM_SIZE))
				return (0);
		}
		else
		{
			if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)) && (inst[1] == '-'
				&& !ft_nisdigit(inst + 2, ft_strlen(inst + 2))) &&
				(ft_atoi(inst + 1) > IDX_MOD || ft_atoi(inst + 1) < -IDX_MOD))
				return (0);
		}
	}
	else if (!check_dirlabel_lastpos(vasm, inst))
		return (0);
	return (1);
}

int		check_dir(t_asm *vasm, char *inst)
{
	if (inst[0] != DIRECT_CHAR)
		return (0);
	else if (!check_dirlabel(vasm, inst))
		return (0);
	else if (inst[0] == DIRECT_CHAR && inst[1] == LABEL_CHAR)
	{
		if (!ft_lstntabstr(&vasm->labreg, inst + 2, ft_strlen(inst + 3), 0))
			return (0);
	}
	return (1);
}

int		check_ind(t_asm *vasm, char *inst)
{
	if (vasm->command >= 13 && vasm->command <= 15)
	{
		if (!ft_nisdigit(inst, ft_strlen(inst)) || ft_atoi(inst) > MEM_SIZE)
			return (0);
	}
	else
	{
		if (!ft_nisdigit(inst, ft_strlen(inst)) || ft_atoi(inst) > IDX_MOD)
			return (0);
	}
	return (1);
}
