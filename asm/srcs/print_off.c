/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:49:52 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/07 17:26:12 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_offset(t_asm *vasm, t_inst *node)
{
	t_inst	*off;
	int		offset;

	offset = 0;
	off = vasm->labreg;
	while (off && ft_strcmp(node->content + 2, off->content))
		off = off->next;
	if (off->line > node->line)
		print_off_pos(vasm, node, off);
	else
		print_off_neg(vasm, node, off);
}

void		print_four_bytes(t_asm *vasm, int val, int offset)
{
	if (offset < 256)
	{
		ft_lprintf(1, "\t%d", val);
		ft_lprintf(1, "\t%d", val);
		ft_lprintf(1, "\t%d", val);
		ft_lprintf(1, "\t%d", offset);
//		write(1, &val, 1);
//		write(1, &val, 1);
//		write(1, &val, 1);
//		write(1, &offset, 1);
	}
	else
	{
		vasm->ret = (offset >> 8) & 0x000000ff;
		ft_lprintf(1, "\t%d", val);
		ft_lprintf(1, "\t%d", val);
		ft_lprintf(1, "\t%d", vasm->ret);
		ft_lprintf(1, "\t%d", offset);
//		write(1, &val, 1);
//		write(1, &val, 1);
//		write(1, &vasm->ret, 1);
//		write(1, &offset, 1);
	}
}

void		print_two_bytes(t_asm *vasm, int val, int offset)
{
	if (offset < 256)
	{
		ft_lprintf(1, "\t%d", val);
		ft_lprintf(1, "\t%d", offset);
//		write(1, &val, 1);
//		write(1, &offset, 1);
	}
	else
	{
		vasm->ret = (offset >> 8) & 0x00ff;
		ft_lprintf(1, "\t%d", vasm->ret);
		ft_lprintf(1, "\t%d", offset);
//		write(1, &vasm->ret, 1);
//		write(1, &offset, 1);
	}
}

void		print_off_pos(t_asm *vasm, t_inst *node, t_inst *off)
{
	t_inst	*tmp;
	int		offset;

	offset = 0;
	tmp = vasm->instruct;
	while (tmp && tmp->line != off->line)
	{
		offset += tmp->content_size;
		tmp = tmp->next;
	}
	while (tmp && ft_strcmp(tmp->content, off->content))
	{
		offset += tmp->content_size;
		tmp = tmp->next;
	}
	if (node->content_size == 4)
		print_four_bytes(vasm, vasm->zero, offset);
	else
		print_two_bytes(vasm, vasm->zero, offset);
}

void		print_off_neg(t_asm *vasm, t_inst *node, t_inst *off)
{
	t_inst	*tmp;
	int		offset;

	tmp = off;
	offset = 0;
	while (tmp && tmp->line != node->line)
	{
		offset += tmp->content_size;
		tmp = tmp->next;
	}
	if (node->content_size == 4)
		print_four_bytes(vasm, vasm->ff, offset);
	else
		print_two_bytes(vasm, vasm->ff, offset);
}
