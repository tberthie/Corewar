/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:27:19 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:18:37 by gthomas          ###   ########.fr       */
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

t_inst		*store_cmd(t_asm *vasm, t_inst *tmp, char *inst, int i)
{
	int		temp;

	if (!vasm->labreg->content)
	{
		first_node(vasm, i, ft_strichr(inst, ' '));
		ft_strncpy(vasm->labreg->content, inst, ft_strichr(inst, ' '));
		temp = ft_stritabstr(vasm->cmd, vasm->labreg->content,
				ft_strlen(vasm->labreg->content));
		tmp = vasm->labreg;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		tmp = other_node(tmp->next, i, ft_strichr(inst, ' '));
		ft_strncpy(tmp->content, inst, ft_strichr(inst, ' '));
		vasm->tmp = tmp->content;
		temp = ft_stritabstr(vasm->cmd, tmp->content, ft_strlen(tmp->content));
	}
	tmp->content_size = 2;
	if (temp == 1 || temp == 9 || temp == 12 || temp == 15)
		tmp->content_size = 1;
	return (tmp);
}

t_inst		*store_inst(t_asm *vasm, t_inst *tmp, char *inst, int i)
{
	int		j;
	int		param;

	param = ft_strichr_cnt(vasm->s[i], SEPARATOR_CHAR);
	j = -1;
	while (++j <= param)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		if (j < param)
		{
			tmp = other_node(tmp->next, i, ft_strichr(inst, SEPARATOR_CHAR));
			ft_strncpy(tmp->content, inst, ft_strichr(inst, SEPARATOR_CHAR));
		}
		else
		{
			tmp = other_node(tmp->next, i, ft_strlen(inst));
			ft_strcpy(tmp->content, inst);
		}
		store_regdirind(vasm, tmp, i, inst);
		inst = inst + ft_strichr(inst, SEPARATOR_CHAR) + 1;
	}
	return (tmp);
}

void		get_labels(t_asm *vasm, int i, int lbl, char *inst)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	i = 0;
	while (i < vasm->file_lines)
	{
		if (ft_stristr(vasm->s[i], NAME_CMD_STRING) == -1 &&
				ft_stristr(vasm->s[i], COMMENT_CMD_STRING) == -1 &&
				vasm->s[i][0] != COMMENT_CHAR)
		{
			lbl = 0;
			if (ft_strichr(vasm->s[i], LABEL_CHAR) > 0 && (vasm->s[i]
				[ft_strichr(vasm->s[i], LABEL_CHAR) - 1] != DIRECT_CHAR))
			{
				lbl = ft_strichr(vasm->s[i], LABEL_CHAR) + 1;
				lbl += ft_trim(vasm->s[i] + lbl);
				tmp = store_label(vasm, tmp, i);
			}
			inst = vasm->s[i] + lbl + ft_trim(vasm->s[i] + lbl);
			tmp = store_cmd(vasm, tmp, inst, i);
			inst += ft_strichr(inst, ' ') + 1;
			tmp = store_inst(vasm, tmp, inst, i);
		}
		++i;
	}
}
