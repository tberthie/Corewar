/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:44:53 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/16 14:44:49 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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
				tmp = check_comment(vasm, tmp->next);
				if ((int)tmp->line != i)
					error(vasm, 10);
			}
			tmp = tmp->next;
		}
		i = tmp->line;
	}
}

t_inst		*check_nb_header(t_asm *vasm)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (tmp)
	{
		if (!ft_strcmp(NAME_CMD_STRING, tmp->content))
			vasm->n += 1;
		if (!ft_strcmp(COMMENT_CMD_STRING, tmp->content))
			vasm->c += 1;
		tmp = tmp->next;
	}
	if (vasm->n > 1 || vasm->c > 1)
		error(vasm, 16);
	return (vasm->labreg);
}

t_inst		*check_header(t_asm *vasm, int name, int comment)
{
	t_inst	*tmp;

	tmp = check_nb_header(vasm);
	while (tmp && tmp->content)
	{
		if (!ft_strcmp(NAME_CMD_STRING, tmp->content))
			name = tmp->line;
		else if (!ft_strcmp(COMMENT_CMD_STRING, tmp->content))
			comment = tmp->line;
		else if (ft_strichr(tmp->content, '"') == -1 &&
				tmp->content[0] != COMMENT_CHAR)
			vasm->first_line = tmp->line;
		if (name && comment && vasm->first_line)
			break ;
		tmp = tmp->next;
	}
	!name ? error(vasm, 1) : 0;
	!comment ? error(vasm, 2) : 0;
	!vasm->first_line ? error(vasm, 7) : 0;
	if (vasm->first_line < name || vasm->first_line < comment)
		error(vasm, 6);
	else if (vasm->first_line == name || vasm->first_line == comment)
		error(vasm, 8);
	check_header_data(vasm, vasm->labreg, 1);
	return (tmp);
}

void		check_asm(t_asm *vasm, t_inst *tmp, t_inst *tmp2)
{
	if (!(tmp = check_header(vasm, 0, 0)))
		error(vasm, 7);
	while (tmp)
	{
		vasm->inst_line = tmp->line;
		if (!tmp->content_size && tmp->content[ft_strlen(tmp->content) - 1] ==
				LABEL_CHAR)
		{
			check_label(vasm, tmp);
			if (!(tmp = tmp->next))
				error(vasm, 3);
		}
		vasm->command = ft_stritabstr(vasm->cmd, tmp->content);
		if (vasm->command == -1)
			error(vasm, 3);
		tmp2 = tmp;
		if (!(tmp = tmp->next))
			error(vasm, 3);
		tmp = vasm->checktab[vasm->command](vasm, tmp);
		if (tmp2->line != vasm->instruct->line)
			error(vasm, 8);
	}
}
