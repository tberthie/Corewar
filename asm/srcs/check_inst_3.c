/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:49:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 15:34:44 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_inst		*check_sti(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	i = 0;
	if ((param = get_param(tmp)) != 5)
		error(vasm, 3);
	while (i < param)
	{
		if (!i && !check_reg(tmp->content))
			error(vasm, 3);
		if ((i == 2) && !check_reg(tmp->content) && !check_dir(vasm,
				tmp->content) && !check_ind(vasm, tmp->content))
			error(vasm, 3);
		if (i == 4 && !check_dir(vasm, tmp->content) &&
				!check_reg(tmp->content))
			error(vasm, 3);
		if ((i % 2) && ft_strlen(tmp->content) != 1 &&
				tmp->content[0] != ',')
			error(vasm, 3);
		if (i == param - 1)
			vasm->instruct = tmp;
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

t_inst		*check_fork(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 1)
		error(vasm, 3);
	if (!check_dir(vasm, tmp->content))
		error(vasm, 3);
	vasm->instruct = tmp;
	return (tmp->next);
}

t_inst		*check_lld(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 3)
		error(vasm, 3);
	while (i < param)
	{
		if (!i && (!check_dir(vasm, tmp->content) && !check_ind(vasm,
				tmp->content)))
			error(vasm, 3);
		if (i == 2 && !check_reg(tmp->content))
			error(vasm, 3);
		if ((i % 2) && ft_strlen(tmp->content) != 1 &&
				tmp->content[0] != ',')
			error(vasm, 3);
		if (i == param - 1)
			vasm->instruct = tmp;
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

t_inst		*check_lldi(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 5)
		error(vasm, 3);
	while (i < param)
	{
		if (!i && !check_reg(tmp->content) && !check_dir(vasm, tmp->content) &&
				!check_ind(vasm, tmp->content))
			error(vasm, 3);
		if (i == 2 && !check_reg(tmp->content) && !check_dir(vasm,
				tmp->content))
			error(vasm, 3);
		if (i == 4 && !check_reg(tmp->content))
			error(vasm, 3);
		if ((i % 2) && ft_strlen(tmp->content) != 1 && tmp->content[0] != ',')
			error(vasm, 3);
		if (i == param - 1)
			vasm->instruct = tmp;
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

t_inst		*check_lfork(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 1)
		error(vasm, 3);
	if (!check_dir(vasm, tmp->content))
		error(vasm, 3);
	vasm->instruct = tmp;
	return (tmp->next);
}
