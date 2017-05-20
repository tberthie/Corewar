/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:27:19 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/20 13:37:30 by gthomas          ###   ########.fr       */
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

t_inst		*store_inst(t_asm *vasm, t_inst *tmp, char *inst, int i)
{
	inst = NULL;
	while (tmp && ft_stritabstr(vasm->cmd, tmp->content,
			ft_strlen(tmp->content)) == -1)
	{
		store_regdirind(vasm, tmp, i, tmp->content);
		tmp = tmp->next;
	}
	return (tmp);
}

t_inst		*store_cmd(t_asm *vasm, t_inst *tmp, char *inst, int i)
{
	int		temp;

	inst = NULL;
	i = 0;
	if (tmp)
	{
		vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
				ft_strlen(tmp->content));
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

void		get_labels(t_asm *vasm, int i, int lbl, char *inst)
{
	t_inst	*tmp;

	get_str(vasm, i, inst);
	tmp = vasm->labreg;
	tmp = get_first_inst(vasm, tmp);
	while (tmp)
	{
		lbl = 0;
		tmp = store_cmd(vasm, tmp, inst, i);
		tmp = store_inst(vasm, tmp, inst, i);
	}
	tmp = vasm->labreg;
	while (tmp)
	{
		tmp = tmp->next;
	}
}
