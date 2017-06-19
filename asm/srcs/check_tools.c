/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:27:15 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/31 13:48:23 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		check_label(t_asm *vasm, t_inst *tmp)
{
	int		i;
	int		len;
	t_inst	*tmp2;

	i = 0;
	len = ft_strlen(tmp->content) - 1;
	tmp2 = vasm->labreg;
	while (i < len)
	{
		if (ft_strichr(LABEL_CHARS, tmp->content[i]) == -1)
			error(vasm, 3);
		++i;
	}
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->content, tmp->content) && tmp2->line < tmp->line)
			error(vasm, 11);
		if (tmp2->line >= tmp->line)
			break ;
		tmp2 = tmp2->next;
	}
}

int			get_param(t_inst *tmp)
{
	t_inst	*tmp2;
	int		i;
	int		param;

	tmp2 = tmp;
	i = tmp->line;
	param = 0;
	while (tmp2 && (int)tmp2->line == i)
	{
		++param;
		tmp2 = tmp2->next;
	}
	return (param);
}

t_inst		*first_inst(t_asm *vasm)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (tmp)
	{
		if (!ft_stritabstr(vasm->cmd, tmp->content))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_inst		*check_name(t_asm *vasm, t_inst *tmp)
{
	if (ft_strichr_cnt(tmp->content, '"') != 2)
		error(vasm, 12);
	if (ft_strichr_last(tmp->content, '"') - ft_strichr(tmp->content, '"') >
			PROG_NAME_LENGTH)
		error(vasm, 14);
	if (ft_strichr_last(tmp->content, '"') - ft_strichr(tmp->content, '"') == 1)
		error(vasm, 17);
	return (tmp);
}

t_inst		*check_comment(t_asm *vasm, t_inst *tmp)
{
	if (ft_strichr_cnt(tmp->content, '"') != 2)
		error(vasm, 13);
	if (ft_strichr_last(tmp->content, '"') - ft_strichr(tmp->content, '"') >
			COMMENT_LENGTH)
		error(vasm, 15);
	if (ft_strichr_last(tmp->content, '"') - ft_strichr(tmp->content, '"') == 1)
		error(vasm, 17);
	return (tmp);
}
