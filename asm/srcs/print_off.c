/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:49:52 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 11:05:55 by gthomas          ###   ########.fr       */
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
	ft_lprintf(1, "%d\t\t", offset);
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
	ft_lprintf(1, "%d\t\t", offset);
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

void		print_four_bytes(t_asm *vasm, int offset)
{
	vasm->ret = (offset >> 24) & 0x000000ff;
	if (vasm->ret >= 100)
		ft_lprintf(1, "%d ", vasm->ret);
	else if (vasm->ret >= 10)
		ft_lprintf(1, "%d  ", vasm->ret);
	else
		ft_lprintf(1, "%d   ", vasm->ret);
	vasm->ret = (offset >> 16) & 0x000000ff;
	if (vasm->ret >= 100)
		ft_lprintf(1, "%d ", vasm->ret);
	else if (vasm->ret >= 10)
		ft_lprintf(1, "%d  ", vasm->ret);
	else
		ft_lprintf(1, "%d   ", vasm->ret);
	vasm->ret = (offset >> 8) & 0x000000ff;
	if (vasm->ret >= 100)
		ft_lprintf(1, "%d ", vasm->ret);
	else if (vasm->ret >= 10)
		ft_lprintf(1, "%d  ", vasm->ret);
	else
		ft_lprintf(1, "%d   ", vasm->ret);
	vasm->ret = offset & 0x000000ff;
	ft_lprintf(1, "%d\t", vasm->ret);
}

void		print_two_bytes(t_asm *vasm, int offset)
{
	vasm->ret = (offset >> 8) & 0x000000ff;
	if (vasm->ret >= 100)
		ft_lprintf(1, "%d ", vasm->ret);
	else if (vasm->ret >= 10)
		ft_lprintf(1, "%d  ", vasm->ret);
	else
		ft_lprintf(1, "%d   ", vasm->ret);
	vasm->ret = offset & 0x000000ff;
	ft_lprintf(1, "%d\t\t", vasm->ret);
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
		print_four_bytes(vasm, offset);
	else
		print_two_bytes(vasm, offset);
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
		print_four_bytes(vasm, offset * -1);
	else
		print_two_bytes(vasm, offset * -1);
}
