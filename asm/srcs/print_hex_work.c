/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:27:21 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 10:35:10 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_cmd(t_asm *vasm, t_inst *node)
{
	int vocp;
	int cmd;

	cmd = vasm->command;
	ft_lprintf(1, "\n\t\t%d", vasm->command);
	vasm->len = 16;
	vocp = 0;
	if (cmd != 1 && cmd != 9 && cmd != 12 && cmd != 15)
	{
		vocp = find_ocp(node, 0, 0, 0);
		ft_lprintf(1, "  %d", vocp);
	}
	if (vocp)
		vasm->len -= ft_intlen(vocp);
	vasm->len -= ft_intlen(vasm->command);
}

void		print_reg(t_asm *vasm, t_inst *node)
{
	int reg;

	reg = ft_atoi(node->content + 1);
	vasm->len = 16 - ft_intlen(reg);
	ft_lprintf(1, "\t\t%d", reg);
}

void		print_dir_int(t_asm *vasm, t_inst *node, int dir)
{
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		ft_lprintf(1, "\t\t%d", dir);
		vasm->len = 16 - ft_intlen(dir);
	}
	else
		print_offset_int(vasm, node);
}

void		print_dir_neg(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	ft_lprintf(1, "\t\t");
	while (i < node->content_size - 2)
	{
		ft_lprintf(1, "255 ");
		++i;
	}
	if (dir > -256)
	{
		ft_lprintf(1, "255 ");
		vasm->len = 4;
	}
	else
	{
		vasm->ret = (dir >> 8) & 0x000000ff;
		ft_lprintf(1, "%d ", vasm->ret);
		vasm->len = 4 - ft_intlen(vasm->ret) - 1;
	}
}

void		print_dir(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		if (dir >= 0)
		{
			ft_lprintf(1, "\t\t");
			while (i < node->content_size - 2)
			{
				ft_lprintf(1, "0   ");
				++i;
			}
			if (dir < 256)
			{
				ft_lprintf(1, "0   ");
			}
			else
			{
				vasm->ret = (dir >> 8) & 0x000000ff;
				if (vasm->ret >= 100)
					ft_lprintf(1, "%d ", vasm->ret);
				else if (vasm->ret > 10)
					ft_lprintf(1, "%d  ", vasm->ret);
				else
					ft_lprintf(1, "%d   ", vasm->ret);
			}
			vasm->len = 4;
		}
		else
			print_dir_neg(vasm, node, dir, i);
		vasm->acor = dir;
		ft_lprintf(1, "%d", vasm->acor);
		vasm->len -= ft_intlen(vasm->acor);
	}
	else
		print_offset(vasm, node);
}

void		print_ind_int(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]))
	{
		ind = ft_atoi(node->content);
		ft_lprintf(1, "\t\t%d", ind);
	}
	else
		print_offset_int(vasm, node);
}

void		print_ind(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]))
	{
		ft_lprintf(1, "\t\t");
		ind = ft_atoi(node->content);
		vasm->ret = (ind >> 8) & 0x00ff;
		if (ind < 256)
			ft_lprintf(1, "0  ");
		else
			ft_lprintf(1, "%d  ", vasm->ret);
		ft_lprintf(1, "%d", ind);
		vasm->len = 16 - 4 - ft_intlen(ind);
	}
	else
		print_offset(vasm, node);
}
