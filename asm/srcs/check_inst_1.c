/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:37:01 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/07 14:29:20 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_live(t_asm *vasm, char *inst)
{
	int		param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm, 3);
	if (!check_dir(vasm, inst))
		error(vasm, 3);
}

void		check_ld(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 1)
		error(vasm, 3);
	while (i <= param)
	{
		if ((i && !check_reg(inst)) && (!i && !check_dir(vasm, inst) &&
					!check_ind(vasm, inst)))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void		check_st(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 1)
		error(vasm, 3);
	while (i <= param)
	{
		if (!check_reg(inst) && (i && !check_ind(vasm, inst)))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void		check_add(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm, 3);
	while (i <= param)
	{
		if (!check_reg(inst))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void		check_sub(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm, 3);
	while (i <= param)
	{
		if (!check_reg(inst))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}
