/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:27:19 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/19 11:57:01 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_inst		*store_label(t_asm *vasm, t_inst *tmp, int i)
{
	if (!vasm->labreg->content)
	{
		first_node(vasm, i, ft_strichr(vasm->s[i], LABEL_CHAR));
		ft_strncpy(vasm->labreg->content, vasm->s[i], ft_strichr(vasm->s[i],
				LABEL_CHAR));
		tmp = vasm->labreg;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		tmp = other_node(tmp->next, i, ft_strichr(vasm->s[i], LABEL_CHAR));
		ft_strncpy(tmp->content, vasm->s[i], ft_strichr(vasm->s[i],
					LABEL_CHAR));
	}
	return (tmp);
}

t_inst		*store_inst(t_asm *vasm, t_inst *tmp, int i)
{
	while (tmp && ft_stritabstr(vasm->cmd, tmp->content) == -1)
	{
		store_regdirind(vasm, tmp, i, tmp->content);
		tmp = tmp->next;
	}
	return (tmp);
}

t_inst		*store_cmd(t_asm *vasm, t_inst *tmp, int i)
{
	int		temp;

	i = 0;
	if (tmp)
	{
		vasm->command = ft_stritabstr(vasm->cmd, tmp->content);
		temp = vasm->command;
		if (temp != -1)
		{
			tmp->content_size = 2;
			if (temp == 1 || temp == 9 || temp == 12 || temp == 15)
				tmp->content_size = 1;
			return (tmp->next);
		}
	}
	return (tmp);
}

void		get_labels(t_asm *vasm, int i, int lbl)
{
	t_inst	*tmp;

	get_str(vasm, i);
	if (!(tmp = vasm->labreg))
		error(vasm, 7);
	if (!(tmp = get_first_inst(tmp)))
		error(vasm, 7);
	while (tmp)
	{
		lbl = 0;
		tmp = store_cmd(vasm, tmp, i);
		tmp = store_inst(vasm, tmp, i);
	}
}
