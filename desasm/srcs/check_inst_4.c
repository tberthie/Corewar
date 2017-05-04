/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:35:38 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/02 14:36:07 by gthomas          ###   ########.fr       */
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
		error(vasm);
	if (!check_reg(inst))
		error(vasm);
}
