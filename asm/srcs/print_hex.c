/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:27:21 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 15:39:51 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_cmd(t_asm *vasm, t_inst *node)
{
	int vocp;
	int cmd;

	cmd = vasm->command;
	ft_lprintf(1, "\n\t\t%d", vasm->command);
	vocp = 0;
	if (cmd != 1 && cmd != 9 && cmd != 12 && cmd != 15)
	{
		vocp = find_ocp(node, 0, 0, 0);
		ft_lprintf(1, "  %d\t\t", vocp);
	}
	else
		ft_lprintf(1, "\t\t");
}

void		print_reg(t_inst *node)
{
	int reg;

	reg = ft_atoi(node->content + 1);
	ft_lprintf(1, "%d\t\t", reg);
}

void		print_ind_int(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]) || (node->content[0] == '-' &&
			ft_isdigit(node->content[1])))
	{
		ind = ft_atoi(node->content);
		ft_lprintf(1, "%d\t\t", ind);
	}
	else
		print_offset_int(vasm, node);
}

void		print_ind(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]) || (node->content[0] == '-' &&
			ft_isdigit(node->content[1])))
	{
		ind = ft_atoi(node->content);
		print_two_bytes(vasm, ind);
	}
	else
		print_offset(vasm, node);
}
