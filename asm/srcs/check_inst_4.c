/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:35:38 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/07 14:30:14 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	check_none(t_asm *vasm, char *inst)
{
	inst[0] = '\0';
	vasm->inst = 0;
}

void	check_aff(t_asm *vasm, char *inst)
{
	int param;

	param = ft_strichr_cnt(inst, SEPARATOR_CHAR);
	if (param)
		error(vasm, 3);
	if (!check_reg(inst))
		error(vasm, 3);
}
