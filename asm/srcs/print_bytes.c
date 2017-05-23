/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 11:09:55 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/20 13:59:34 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_inst_size(t_asm *vasm, int label)
{
	if (!label)
		ft_lprintf(1, "\n\n%d", vasm->bytes);
	else
		ft_lprintf(1, "%d", vasm->bytes);
	vasm->bytes += vasm->size;
	label = 0;
	if (vasm->size >= 10)
	{
		if (vasm->bytes >= 100)
			ft_lprintf(1, " (%d) :", vasm->size);
		else if (vasm->bytes >= 10)
			ft_lprintf(1, "  (%d) :", vasm->size);
		else
			ft_lprintf(1, "   (%d) :", vasm->size);
	}
	else
	{
		if (vasm->bytes >= 100)
			ft_lprintf(1, " (%d ) :", vasm->size);
		else if (vasm->bytes >= 10)
			ft_lprintf(1, "  (%d ) :", vasm->size);
		else
			ft_lprintf(1, "   (%d ) :", vasm->size);
	}
}

void		print_size(t_asm *vasm, t_inst *tmp2, t_inst *tmp, int label)
{
	while (tmp2 && vasm->inst_line == (int)tmp2->line)
	{
		vasm->size += tmp2->content_size;
		tmp2 = tmp2->next;
	}
	tmp2 = tmp;
	if (vasm->inst_line == (int)tmp2->line && !tmp2->content_size)
	{
		if (tmp == vasm->labreg)
			ft_lprintf(1, "%d", vasm->bytes);
		else
			ft_lprintf(1, "\n\n%d", vasm->bytes);
		ft_lprintf(1, "\t :   %s\n", tmp2->content);
		label = 1;
		tmp2 = tmp2->next;
	}
	if (tmp2 && vasm->inst_line == (int)tmp2->line && tmp2->content_size)
		print_inst_size(vasm, label);
	vasm->size = 0;
}
