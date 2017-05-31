/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:49:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/24 17:25:16 by gthomas          ###   ########.fr       */
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

int		check_dirlabel_1(t_asm *vasm, char *inst)
{
	if (vasm->command >= 13 && vasm->command <= 15)
	{
		if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)))
		{
			if (inst[1] != '-')
				return (0);
			if (inst[1] == '-' && !ft_nisdigit(inst + 2, ft_strlen(inst + 2)))
				return (0);
		}
	}
	else
	{
		if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)))
		{
			if (inst[1] != '-')
				return (0);
			if (inst[1] == '-' && !ft_nisdigit(inst + 2, ft_strlen(inst + 2)))
				return (0);
		}
	}
	return (1);
}

int		check_dirlabel(t_asm *vasm, char *inst)
{
	if (inst[0] == DIRECT_CHAR && inst[1] != LABEL_CHAR)
	{
		if (!check_dirlabel_1(vasm, inst))
			return (0);
	}
	return (1);
}

int		check_dir(t_asm *vasm, char *inst)
{
	if (inst[0] != DIRECT_CHAR || ft_strlen(inst) < 2)
		return (0);
	else if (!check_dirlabel(vasm, inst))
		return (0);
	else if (inst[0] == DIRECT_CHAR && inst[1] == LABEL_CHAR)
	{
		if (!ft_lstntabstr(&vasm->labreg, inst + 2, ft_strlen(inst + 2), 0))
			return (0);
	}
	return (1);
}

int		check_ind(t_asm *vasm, char *inst)
{
	if (!ft_lstntabstr(&vasm->labreg, inst + 1, ft_strlen(inst + 1), 0) &&
			!ft_nisdigit(inst, ft_strlen(inst)) && (inst[0] != '-' ||
			(inst[0] == '-' && !ft_nisdigit(inst + 1,
			ft_strlen(inst + 1)))))
		return (0);
	return (1);
}
