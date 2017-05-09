/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:49:52 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/09 14:58:19 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_off_pos_int(t_asm *vasm, t_inst *off)
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
	ft_lprintf(1, "\t%d", offset);
}

void		print_off_neg_int(t_inst *node, t_inst *off)
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
	offset *= -1;
	ft_lprintf(1, "\t%d", offset);
}

void		print_offset_int(t_asm *vasm, t_inst *node)
{
	t_inst	*off;
	int		offset;

	offset = 0;
	off = vasm->labreg;
	while (off && ft_strcmp(node->content + 2, off->content))
		off = off->next;
	if (off->line > node->line)
		print_off_pos_int(vasm, off);
	else
		print_off_neg_int(node, off);
}

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
	ft_lprintf(1, "\t");
	val = 0;
//	if (offset < 256)
//	{
//		ft_lprintf(1, "%d ", val);
//		ft_lprintf(1, "%d ", val);
//		ft_lprintf(1, "%d ", val);
//		ft_lprintf(1, "%d ", offset);
//		write(1, &val, 1);
//		write(1, &val, 1);
//		write(1, &val, 1);
//		write(1, &offset, 1);
//	}
//	else
//	{
		vasm->ret = (offset >> 24) & 0x000000ff;
		ft_lprintf(1, "%d ", vasm->ret);//val);
		vasm->ret = (offset >> 16) & 0x000000ff;
		ft_lprintf(1, "%d ", vasm->ret);////val);
		vasm->ret = (offset >> 8) & 0x000000ff;
		ft_lprintf(1, "%d ", vasm->ret);
		vasm->ret = offset & 0x000000ff;
		ft_lprintf(1, "%d ", vasm->ret);//offset);
//		write(1, &val, 1);
//		write(1, &val, 1);
//		write(1, &vasm->ret, 1);
//		write(1, &offset, 1);
//	}
}

void		print_two_bytes(t_asm *vasm, int val, int offset)
{
	ft_lprintf(1, "\t");
	val = 0;
	vasm->ret = (offset >> 8) & 0x000000ff;
	ft_lprintf(1, "%d ", vasm->ret);
	vasm->ret = offset & 0x000000ff;
	ft_lprintf(1, "%d ", vasm->ret);//offset);
//	if (offset < 256)
//	{
//		ft_lprintf(1, "%d  ", val);
//		ft_lprintf(1, "%d  ", offset);
//		write(1, &val, 1);
//		write(1, &offset, 1);
//	}
//	else
//	{
///		vasm->ret = (offset >> 8) & 0x00ff;
//		ft_lprintf(1, "%d  ", vasm->ret);
//		ft_lprintf(1, "%d  ", offset);
//		write(1, &vasm->ret, 1);
//		write(1, &offset, 1);
//	}
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
		print_four_bytes(vasm, vasm->ff, offset * -1);
	else
		print_two_bytes(vasm, vasm->ff, offset * -1);
}
