/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:27:21 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/09 14:58:21 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_cmd(t_asm *vasm, t_inst *node)
{
	int vocp;
	int cmd;

	cmd = vasm->command;
	ft_lprintf(1, "\n\t\t%d", vasm->command);//vasm->cmd[vasm->command]);
	vocp = 0;
	if (cmd != 1 && cmd != 9 && cmd != 12 && cmd != 15)
	{
		vocp = find_ocp(node, 0, 0, 0);
		ft_lprintf(1, "  %d", vocp);//write(1, &vocp, 1);
	}
}

void		print_reg(t_inst *node)
{
	int reg;

	reg = ft_atoi(node->content + 1);
	ft_lprintf(1, "\t%d", reg);//write(1, &reg, 1);
}

void		print_dir_int(t_asm *vasm, t_inst *node, int dir)
{
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
/*		if (dir >= 0)
		{
			ft_lprintf(1, "\t");
			while (i < node->content_size - 2)
			{
				ft_lprintf(1, "0  ");//write(1, &vasm->zero, 1);
				++i;
			}
			if (dir < 256)
				ft_lprintf(1, "0  ");//write(1, &vasm->zero, 1);
			else
			{
				vasm->ret = (dir >> 8) & 0x000000ff;
				ft_lprintf(1, "%d  ", vasm->ret);//write(1, &vasm->ret, 1);
			}
		}
		else
			print_dir_int_neg(vasm, node, dir, i);
		vasm->acor = dir;*/
		ft_lprintf(1, "\t%d", dir);//write(1, &dir, 1);
	}
	else
		print_offset_int(vasm, node);
}

void		print_dir_neg(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	ft_lprintf(1, "\t");
	while (i < node->content_size - 2)
	{
		ft_lprintf(1, "255 ");//write(1, &vasm->ff, 1);
		++i;
	}
	if (dir > -256)
		ft_lprintf(1, "255 ");//write(1, &vasm->ff, 1);
	else
	{
		vasm->ret = (dir >> 8) & 0x000000ff;
		ft_lprintf(1, "%d ", vasm->ret);//write(1, &vasm->ret, 1);
	}
}

void		print_dir(t_asm *vasm, t_inst *node, int dir, size_t i)
{
//	ft_lprintf(1, "la\n");
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		if (dir >= 0)
		{
			ft_lprintf(1, "\t");
			while (i < node->content_size - 2)
			{
				ft_lprintf(1, "0  ");//write(1, &vasm->zero, 1);
				++i;
			}
			if (dir < 256)
				ft_lprintf(1, "0  ");//write(1, &vasm->zero, 1);
			else
			{
				vasm->ret = (dir >> 8) & 0x000000ff;
				ft_lprintf(1, "\n%d  ", vasm->ret);//write(1, &vasm->ret, 1);
			}
		}
		else
			print_dir_neg(vasm, node, dir, i);
		vasm->acor = dir;
		ft_lprintf(1, "%d", vasm->acor);//write(1, &dir, 1);
	}
	else
	{
//		ft_lprintf(1, "Je suis ici\n");
		print_offset(vasm, node);
	}
}

void		print_ind_int(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]))
	{
//		ft_lprintf(1, "\t");
		ind = ft_atoi(node->content);
//		vasm->ret = (ind >> 8) & 0x00ff;
//		if (ind < 256)
//			ft_lprintf(1, "0  ");//write(1, &vasm->zero, 1);
//		else
//			ft_lprintf(1, "%d  ", vasm->ret);//write(1, &vasm->ret, 1);
		ft_lprintf(1, "\t%d", ind);//write(1, &ind, 1);
	}
	else
		print_offset_int(vasm, node);
}

void		print_ind(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]))
	{
		ft_lprintf(1, "\t");
		ind = ft_atoi(node->content);
		vasm->ret = (ind >> 8) & 0x00ff;
		if (ind < 256)
			ft_lprintf(1, "0  ");//write(1, &vasm->zero, 1);
		else
			ft_lprintf(1, "%d  ", vasm->ret);//write(1, &vasm->ret, 1);
		ft_lprintf(1, "%d", ind);//write(1, &ind, 1);
	}
	else
		print_offset(vasm, node);
}
