/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:27:21 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/02 15:15:42 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		put_cmd(t_asm *vasm, t_inst *node)
{
	int vocp;
	int cmd;

	cmd = vasm->command;
	write(vasm->fd, &cmd, 1);
	vocp = 0;
	if (cmd != 1 && cmd != 9 && cmd != 12 && cmd != 15)
	{
		vocp = find_ocp(node, 0, 0, 0);
		write(vasm->fd, &vocp, 1);
	}
}

void		put_reg(t_asm *vasm, t_inst *node)
{
	int reg;

	reg = ft_atoi(node->content + 1);
	write(vasm->fd, &reg, 1);
}

void		put_dir(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	if (ft_isdigit(node->content[1]))
	{
		dir = ft_atoi(node->content + 1);
		while (i < node->content_size - 2)
		{
			write(vasm->fd, &vasm->zero, 1);
			++i;
		}
		if (dir < 256)
			write(vasm->fd, &vasm->zero, 1);
		else
		{
			vasm->ret = (dir >> 8) & 0x000000ff;
			write(vasm->fd, &vasm->ret, 1);
		}
		write(vasm->fd, &dir, 1);
	}
	else
		put_offset(vasm, node);
}

void		put_ind(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]))
	{
		ind = ft_atoi(node->content);
		vasm->ret = (ind >> 8) & 0x00ff;
		if (ind < 256)
			write(vasm->fd, &vasm->zero, 1);
		else
			write(vasm->fd, &vasm->ret, 1);
		write(vasm->fd, &ind, 1);
	}
	else
		put_offset(vasm, node);
}

void		put_asm(t_asm *vasm)
{
	t_inst *tmp;

	tmp = vasm->labreg;
	while (tmp)
	{
		if (tmp->content_size)
		{
			if (tmp->content[0] == 'r')
				put_reg(vasm, tmp);
			else if (ft_nisdigit(tmp->content, ft_strlen(tmp->content)))
				put_ind(vasm, tmp, 0);
			else if (tmp->content[0] == DIRECT_CHAR)
				put_dir(vasm, tmp, 0, 0);
			else
			{
				vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
						ft_strlen(tmp->content));
				vasm->instruct = tmp;
				if (vasm->command >= 0)
					put_cmd(vasm, tmp);
			}
		}
		tmp = tmp->next;
	}
}
