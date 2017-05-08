/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:27:21 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/07 17:27:09 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_cmd(t_asm *vasm, t_inst *node)
{
	int vocp;
	int cmd;

	cmd = vasm->command;
	ft_lprintf(1, "%s\t", vasm->cmd[vasm->command]);
	vocp = 0;
	if (cmd != 1 && cmd != 9 && cmd != 12 && cmd != 15)
	{
		vocp = find_ocp(node, 0, 0, 0);
		ft_lprintf(1, "%x\t", vocp);//write(1, &vocp, 1);
	}
}

void		print_reg(t_inst *node)
{
	int reg;

	reg = ft_atoi(node->content + 1);
	ft_lprintf(1, "\t%d", reg);//write(1, &reg, 1);
}

void		print_dir_neg(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	while (i < node->content_size - 2)
	{
		ft_lprintf(1, "\t255");//write(1, &vasm->ff, 1);
		++i;
	}
	if (dir > -256)
		ft_lprintf(1, "\t255");//write(1, &vasm->ff, 1);
	else
	{
		vasm->ret = (dir >> 8) & 0x000000ff;
		ft_lprintf(1, "\t%d", vasm->ret);//write(1, &vasm->ret, 1);
	}
}

void		print_dir(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		if (dir >= 0)
		{
			while (i < node->content_size - 2)
			{
				ft_lprintf(1, "\t00");//write(1, &vasm->zero, 1);
				++i;
			}
			if (dir < 256)
				ft_lprintf(1, "\t00");//write(1, &vasm->zero, 1);
			else
			{
				vasm->ret = (dir >> 8) & 0x000000ff;
				ft_lprintf(1, "\t%d", vasm->ret);//write(1, &vasm->ret, 1);
			}
		}
		else
			print_dir_neg(vasm, node, dir, i);
		ft_lprintf(1, "\t%d", dir);//write(1, &dir, 1);
	}
	else
		print_offset(vasm, node);
}

void		print_ind(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]))
	{
		ind = ft_atoi(node->content);
		vasm->ret = (ind >> 8) & 0x00ff;
		if (ind < 256)
			ft_lprintf(1, "\t0");//write(1, &vasm->zero, 1);
		else
			ft_lprintf(1, "\t%d", vasm->ret);//write(1, &vasm->ret, 1);
		ft_lprintf(1, "\t%d", ind);//write(1, &ind, 1);
	}
	else
		print_offset(vasm, node);
}
