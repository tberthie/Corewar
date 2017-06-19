/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:49:52 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/24 17:26:44 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		four_bytes(t_asm *vasm, int offset)
{
	vasm->ret = (offset >> 24) & 0x000000ff;
	write(vasm->fd, &vasm->ret, 1);
	vasm->ret = (offset >> 16) & 0x000000ff;
	write(vasm->fd, &vasm->ret, 1);
	vasm->ret = (offset >> 8) & 0x000000ff;
	write(vasm->fd, &vasm->ret, 1);
	vasm->ret = offset & 0x000000ff;
	write(vasm->fd, &vasm->ret, 1);
}

void		two_bytes(t_asm *vasm, int offset)
{
	vasm->ret = (offset >> 8) & 0x000000ff;
	write(vasm->fd, &vasm->ret, 1);
	vasm->ret = offset & 0x000000ff;
	write(vasm->fd, &vasm->ret, 1);
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
		four_bytes(vasm, offset);
	else
		two_bytes(vasm, offset);
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
		four_bytes(vasm, offset * -1);
	else
		two_bytes(vasm, offset * -1);
}
