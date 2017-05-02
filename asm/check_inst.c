/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:49:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/02 11:57:04 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_reg(char *inst)
{
	if (inst[0] != 'r')
		return (0);
	else if (inst[0] == 'r' && (!ft_nisdigit(inst + 1, ft_strichr(inst
			+ 1, SEPARATOR_CHAR)) || ft_atoi(inst + 1) >
				REG_NUMBER))
		return (0);
	return (1);
}

int		check_dir(t_asm *vasm, char *inst)
{
	if (inst[0] != DIRECT_CHAR)
		return (0);
	else if (inst[0] == DIRECT_CHAR && inst[1] != LABEL_CHAR && ft_strichr_cnt(inst
				+ 1, SEPARATOR_CHAR))
	{
		if (!ft_nisdigit(inst + 1, ft_strichr(inst + 1, SEPARATOR_CHAR)) ||
				(inst[1] == '-' && !ft_nisdigit(inst + 2, ft_strichr(inst + 2,
				SEPARATOR_CHAR))))
			return (0);
	}
	else if (inst[0] == DIRECT_CHAR && inst[1] != LABEL_CHAR &&
			!ft_strichr_cnt(inst + 1, SEPARATOR_CHAR))
	{
		if (!ft_nisdigit(inst + 1, ft_strlen(inst + 1)) || (inst[1] == '-' && !ft_nisdigit(inst + 2, ft_strlen(inst + 2))))
			return (0);
	}
	else if (inst[0] == DIRECT_CHAR && inst[1] == LABEL_CHAR &&
			ft_strichr_cnt(inst, SEPARATOR_CHAR))
	{
		if (!ft_lstntabstr(&vasm->labreg, inst + 2, ft_strichr(inst + 2,
						SEPARATOR_CHAR), 0))
			return (0);
	}
	else if (inst[0] == DIRECT_CHAR && inst[1] == LABEL_CHAR &&
			!ft_strichr_cnt(inst, SEPARATOR_CHAR))
	{
		if (!ft_lstntabstr(&vasm->labreg, inst + 2, ft_strlen(inst + 2), 0))
			return (0);
	}
	return (1);
}

int		check_ind(char *inst)
{
	if (!ft_nisdigit(inst, ft_strichr(inst, SEPARATOR_CHAR)) || ft_atoi(inst) >
			MEM_SIZE)
		return (0);
	return (1);
}

void	check_none(t_asm *vasm, char *inst)
{
	inst[0] = '\0';
	vasm->inst = 0;
}

void	check_live(t_asm *vasm, char *inst)
{
	int param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm);
	if (!check_dir(vasm, inst))
		error(vasm);
}

void	check_ld(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 1)
		error(vasm);
	while (i <= param)
	{
		if ((i && !check_reg(inst)) && (!i && !check_dir(vasm, inst) && !check_ind(inst)))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_st(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 1)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && (i && !check_ind(inst)))
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_add(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_sub(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_and(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && ((!i || i == 1) && (!check_dir(vasm, inst) &&
						!check_ind(inst))))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_or(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && ((!i || i == 1) && (!check_dir(vasm, inst) &&
						!check_ind(inst))))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_xor(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && ((!i || i == 1) && (!check_dir(vasm, inst) &&
						!check_ind(inst))))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_zjmp(t_asm *vasm, char *inst)
{
	int param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm);
	if (!check_dir(vasm, inst))
		error(vasm);
}

void	check_ldi(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && ((!i || i == 1) && !check_dir(vasm, inst)) &&
						(!i && !check_ind(inst)))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_sti(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && ((i == 2 || i == 1) && !check_dir(vasm, inst)) &&
						(i == 1 && !check_ind(inst)))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_fork(t_asm *vasm, char *inst)
{
	int param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm);
	if (!check_dir(vasm, inst))
			error(vasm);
}

void	check_lld(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 1)
		error(vasm);
	while (i <= param)
	{
		if ((i == 1 && !check_reg(inst)) && (!i && !check_dir(vasm, inst) && !check_ind(inst)))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_lldi(t_asm *vasm, char *inst)
{
	int param;
	int i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm);
	while (i <= param)
	{
		if (!check_reg(inst) && ((!i || i == 1) && !check_dir(vasm, inst) && !check_ind(inst)))
			error(vasm);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void	check_lfork(t_asm *vasm, char *inst)
{
	int param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm);
	if (!check_dir(vasm, inst))
			error(vasm);
}

void	check_aff(t_asm *vasm, char *inst)
{
	int param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm);
	if (!check_reg(inst))
		error(vasm);
}

