/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 12:27:21 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/24 16:53:01 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		put_cmd(t_asm *vasm, t_inst *node)
{
	int vocp;
	int cmd;

	cmd = vasm->command;
	write(vasm->fd, &cmd, 1);
	vocp = 0;
	if (cmd != 1 && cmd != 9 && cmd != 12 && cmd != 15)
	{
		vocp = find_ocp(node->next, node->line, 0, 0);
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
	i = 0;
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		if (node->content_size == 4)
			four_bytes(vasm, dir);
		else
			two_bytes(vasm, dir);
	}
	else
		put_offset_dir(vasm, node);
}

void		put_ind(t_asm *vasm, t_inst *node, int ind)
{
	if (ft_isdigit(node->content[0]) || (node->content[0] == '-' &&
			ft_isdigit(node->content[1])))
	{
		ind = ft_atoi(node->content);
		if (node->content_size == 4)
			four_bytes(vasm, ind);
		else
			two_bytes(vasm, ind);
	}
	else
		put_offset_ind(vasm, node);
}
