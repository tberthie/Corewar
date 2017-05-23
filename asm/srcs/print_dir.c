/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:05:49 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 14:44:50 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_dir_int(t_asm *vasm, t_inst *node, int dir)
{
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		ft_lprintf(1, "%d\t\t", dir);
	}
	else
		print_offset_int(vasm, node);
}

void		print_dir(t_asm *vasm, t_inst *node, int dir, size_t i)
{
	i = 0;
	if (ft_isdigit(node->content[1]) || node->content[1] == '-')
	{
		dir = ft_atoi(node->content + 1);
		if (node->content_size == 4)
			print_four_bytes(vasm, dir);
		else
			print_two_bytes(vasm, dir);
	}
	else
		print_offset(vasm, node);
}
