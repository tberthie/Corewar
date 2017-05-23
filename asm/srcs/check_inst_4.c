/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:35:38 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 15:40:40 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_inst		*check_none(t_asm *vasm, t_inst *tmp)
{
	if (tmp || !tmp)
		error(vasm, 3);
	return (tmp);
}

t_inst		*check_aff(t_asm *vasm, t_inst *tmp)
{
	int		param;
	int		i;

	param = get_param(tmp);
	i = 0;
	if (param != 1)
		error(vasm, 3);
	if (!check_reg(tmp->content))
		error(vasm, 3);
	vasm->instruct = tmp;
	return (tmp->next);
}
