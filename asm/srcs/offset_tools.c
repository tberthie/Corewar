/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:26:29 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/24 17:27:57 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		put_offset_ind(t_asm *vasm, t_inst *node)
{
	t_inst	*off;
	int		offset;

	offset = 0;
	off = vasm->labreg;
	while (off)
	{
		if (ft_strlen(off->content) > 1 && ft_strlen(node->content) ==
				ft_strlen(off->content) && !ft_strncmp(node->content + 1,
				off->content, ft_strlen(off->content) - 1) &&
				!off->content_size)
			break ;
		off = off->next;
	}
	if (off->line > node->line)
		offset_pos(vasm, node, off);
	else
		offset_neg(vasm, node, off);
}

void		put_offset_dir(t_asm *vasm, t_inst *node)
{
	t_inst	*off;
	int		offset;

	offset = 0;
	off = vasm->labreg;
	while (off)
	{
		if (ft_strlen(off->content) > 2 && ft_strlen(node->content + 1) ==
				ft_strlen(off->content) && !ft_strncmp(node->content + 2,
				off->content, ft_strlen(off->content) - 1) &&
				!off->content_size)
			break ;
		off = off->next;
	}
	if (off->line > node->line)
		offset_pos(vasm, node, off);
	else
		offset_neg(vasm, node, off);
}
