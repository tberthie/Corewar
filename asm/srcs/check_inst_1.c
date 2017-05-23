/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:37:01 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 15:30:35 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_inst		*check_live(t_asm *vasm, t_inst *tmp)
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

t_inst		*check_ld(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	if (param != 3)
		error(vasm, 3);
	i = 0;
	while (i < param)
	{
		if (!i && !check_dir(vasm, tmp->content) && !check_ind(vasm,
				tmp->content))
			error(vasm, 3);
		if (i == 2 && !check_reg(tmp->content))
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

t_inst		*check_st(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 3)
		error(vasm, 3);
	while (i < param)
	{
		if (!i && !check_reg(tmp->content))
			error(vasm, 3);
		if (i == 2 && !check_reg(tmp->content) && !check_ind(vasm,
				tmp->content))
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

t_inst		*check_add(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 5)
		error(vasm, 3);
	while (i < param)
	{
		if (!(i % 2) && !check_reg(tmp->content))
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

t_inst		*check_sub(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 5)
		error(vasm, 3);
	while (i < param)
	{
		if (!(i % 2) && !check_reg(tmp->content))
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
