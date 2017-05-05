/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:37:17 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/04 12:55:14 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_and(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

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

void		check_or(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

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

void		check_xor(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

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

void		check_zjmp(t_asm *vasm, char *inst)
{
	int		param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm);
	if (!check_dir(vasm, inst))
		error(vasm);
}

void		check_ldi(t_asm *vasm, char *inst)
{
	int		param;
	int		i;

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