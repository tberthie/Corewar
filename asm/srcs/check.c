/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:44:53 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/20 13:28:00 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_inst		*first_inst(t_asm *vasm)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (tmp)
	{
		if (!ft_stritabstr(vasm->cmd, tmp->content, ft_strlen(tmp->content)))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_inst		*check_name(t_asm *vasm, t_inst *tmp)
{
	if (ft_strichr_cnt(tmp->content, '"') != 2 ||
			ft_strichr_last(tmp->content, '"') -
			ft_strichr(tmp->content, '"') == 1 ||
			ft_strichr_last(tmp->content, '"') -
			ft_strichr(tmp->content, '"') > PROG_NAME_LENGTH)
		error(vasm, 1);
	return (tmp);
}

void		check_header_data(t_asm *vasm, t_inst *tmp, int i)
{
	while ((int)tmp->line < vasm->first_line)
	{
		while ((int)tmp->line == i)
		{
			i = tmp->line;
			if (!ft_strcmp(NAME_CMD_STRING, tmp->content))
			{
				tmp = check_name(vasm, tmp->next);
				if ((int)tmp->line != i)
					error(vasm, 9);
			}
			if (!ft_strcmp(COMMENT_CMD_STRING, tmp->content))
			{
				tmp = tmp->next;
				if (ft_strichr_cnt(tmp->content, '"') != 2 ||
						ft_strichr_last(tmp->content, '"') -
						ft_strichr(tmp->content, '"') > COMMENT_LENGTH)
					error(vasm, 2);
				if ((int)tmp->line != i)
					error(vasm, 10);
			}
			tmp = tmp->next;
		}
		i = tmp->line;
	}
}

t_inst		*check_header(t_asm *vasm, int name, int comment)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (tmp && !vasm->first_line)
	{
		if (!ft_strcmp(NAME_CMD_STRING, tmp->content))
			name = tmp->line;
		else if (!ft_strcmp(COMMENT_CMD_STRING, tmp->content))
			comment = tmp->line;
		else if (tmp->content[0] != '"')
			vasm->first_line = tmp->line;
		tmp = tmp->next;
	}
	if (!name)
		error(vasm, 1);
	if (!comment)
		error(vasm, 2);
	if (!vasm->first_line)
		error(vasm, 7);
	if (name >= comment || vasm->first_line <= name ||
			vasm->first_line <= comment)
		error(vasm, 6);
	check_header_data(vasm, vasm->labreg, 1);
	return (tmp);
}

void		check_asm(t_asm *vasm, t_inst *tmp, t_inst *tmp2)
{
	tmp = check_header(vasm, 0, 0);
	while (tmp)
	{
		vasm->inst_line = tmp->line;
		if (!tmp->content_size && tmp->content[ft_strlen(tmp->content) - 1] ==
				LABEL_CHAR)
		{
			check_label(vasm, tmp);
			tmp = tmp->next;
		}
		else
		{
			vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
					ft_strlen(tmp->content));
			if (vasm->command == -1)
				error(vasm, 3);
			tmp2 = tmp;
			tmp = tmp->next;
			tmp = vasm->checktab[vasm->command](vasm, tmp);
			if (tmp2->line != vasm->instruct->line)
				error(vasm, 8);
		}
	}
}
