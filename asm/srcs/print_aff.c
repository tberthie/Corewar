/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 11:40:20 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:46:32 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_inst(t_asm *vasm, t_inst *tmp2, t_inst *tmp)
{
	while (tmp2 && vasm->inst_line == (int)tmp2->line)
	{
		if (tmp2->content_size)
		{
			if (tmp2->content[0] != 'r' && tmp2->content[0] != DIRECT_CHAR &&
					!ft_isdigit(tmp2->content[0]))
				ft_lprintf(1, "\t%s", tmp2->content);
			else
				ft_lprintf(1, "\t\t%s", tmp2->content);
		}
		tmp2 = tmp2->next;
	}
	tmp2 = tmp;
}

void		print_data(t_asm *vasm, t_inst *tmp2, t_inst *tmp)
{
	while (tmp2 && vasm->inst_line == (int)tmp2->line)
	{
		if (tmp2->content_size)
		{
			if (tmp2->content[0] == 'r')
				print_reg(tmp2);
			else if (ft_nisdigit(tmp2->content, ft_strlen(tmp2->content)))
				print_ind(vasm, tmp2, 0);
			else if (tmp2->content[0] == DIRECT_CHAR)
				print_dir(vasm, tmp2, 0, 0);
			else
			{
				vasm->command = ft_stritabstr(vasm->cmd, tmp2->content,
						ft_strlen(tmp2->content));
				vasm->instruct = tmp;
				if (vasm->command >= 0)
					print_cmd(vasm, tmp2);
			}
		}
		tmp2 = tmp2->next;
	}
}

t_inst		*print_cor_int(t_asm *vasm, t_inst *tmp)
{
	if (tmp->content_size)
	{
		if (tmp->content[0] == 'r')
			print_reg(tmp);
		else if (ft_nisdigit(tmp->content, ft_strlen(tmp->content)))
			print_ind_int(vasm, tmp, 0);
		else if (tmp->content[0] == DIRECT_CHAR)
			print_dir_int(vasm, tmp, 0);
		else
		{
			vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
					ft_strlen(tmp->content));
			vasm->instruct = tmp;
			if (vasm->command >= 0)
				print_cmd(vasm, tmp);
		}
	}
	tmp = tmp->next;
	return (tmp);
}

void		print_asm(t_asm *vasm)
{
	t_inst	*tmp;
	t_inst	*tmp2;

	tmp = vasm->labreg;
	tmp2 = tmp;
	while (tmp)
	{
		if (vasm->inst_line != (int)tmp->line)
		{
			tmp2 = tmp;
			vasm->inst_line = (int)tmp2->line;
			print_size(vasm, tmp2, tmp, 0);
			print_inst(vasm, tmp2, tmp);
			print_data(vasm, tmp2, tmp);
		}
		tmp = print_cor_int(vasm, tmp);
	}
	ft_lprintf(1, "\n");
}
