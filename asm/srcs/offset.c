/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:49:52 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/07 14:23:55 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		put_offset(t_asm *vasm, t_inst *node)
{
	t_inst	*off;
	int		offset;

	offset = 0;
	off = vasm->labreg;
	while (off && ft_strcmp(node->content + 2, off->content))
		off = off->next;
	if (off->line > node->line)
		offset_pos(vasm, node, off);
	else
		offset_neg(vasm, node, off);
}

void		four_bytes(t_asm *vasm, int val, int offset)
{
	if (offset < 256)
	{
		write(vasm->fd, &val, 1);
		write(vasm->fd, &val, 1);
		write(vasm->fd, &val, 1);
		write(vasm->fd, &offset, 1);
	}
	else
	{
		vasm->ret = (offset >> 8) & 0x000000ff;
		write(vasm->fd, &val, 1);
		write(vasm->fd, &val, 1);
		write(vasm->fd, &vasm->ret, 1);
		write(vasm->fd, &offset, 1);
	}
}

void		two_bytes(t_asm *vasm, int val, int offset)
{
	if (offset < 256)
	{
		write(vasm->fd, &val, 1);
		write(vasm->fd, &offset, 1);
	}
	else
	{
		vasm->ret = (offset >> 8) & 0x00ff;
		write(vasm->fd, &vasm->ret, 1);
		write(vasm->fd, &offset, 1);
	}
}

void		offset_pos(t_asm *vasm, t_inst *node, t_inst *off)
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
		four_bytes(vasm, vasm->zero, offset);
	else
		two_bytes(vasm, vasm->zero, offset);
}

void		offset_neg(t_asm *vasm, t_inst *node, t_inst *off)
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
		four_bytes(vasm, vasm->ff, offset);
	else
		two_bytes(vasm, vasm->ff, offset);
}
