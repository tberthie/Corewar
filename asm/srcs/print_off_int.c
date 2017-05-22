/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_off_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:13:18 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/20 14:39:23 by gthomas          ###   ########.fr       */
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
	while (tmp && ft_strncmp(tmp->content, off->content,
			ft_strlen(tmp->content) - 1))
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
	while (off && ft_strncmp(node->content + 2, off->content,
			ft_strlen(off->content) - 1))
		off = off->next;
	if (off->line > node->line)
		print_off_pos_int(vasm, off);
	else
		print_off_neg_int(node, off);
}
