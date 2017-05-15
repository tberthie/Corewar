/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:49:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 12:52:23 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_sti(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm, 3);
	while (i <= param)
	{
		if (!check_reg(inst) && ((i == 2 || i == 1) && !check_dir(vasm, inst))
				&& (i == 1 && !check_ind(vasm, inst)))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void		check_fork(t_asm *vasm, char *inst)
{
	int		param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm, 3);
	if (!check_dir(vasm, inst))
		error(vasm, 3);
}

void		check_lld(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 1)
		error(vasm, 3);
	while (i <= param)
	{
		if ((i == 1 && !check_reg(inst)) && (!i && !check_dir(vasm, inst) &&
					!check_ind(vasm, inst)))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void		check_lldi(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	i = 0;
	if (param != 2)
		error(vasm, 3);
	while (i <= param)
	{
		if (!check_reg(inst) && ((!i || i == 1) && !check_dir(vasm, inst) &&
					!check_ind(vasm, inst)))
			error(vasm, 3);
		if (i < param)
			inst += ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++i;
	}
}

void		check_lfork(t_asm *vasm, char *inst)
{
	int		param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm, 3);
	if (!check_dir(vasm, inst))
		error(vasm, 3);
}
