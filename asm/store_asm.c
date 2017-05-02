/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:27:19 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/02 11:57:06 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_lstntabstr(t_inst **begin, char *str, int size, int nb)
{
	t_inst *tmp;

	tmp = *begin;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, str, size) && nb == (int)tmp->content_size)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_inst	*store_label(t_asm *vasm, t_inst *tmp, int i)
{
	if (!vasm->labreg->content)
	{
		if (!(vasm->labreg->content = (char *)malloc(ft_strichr(vasm->s[i],
							LABEL_CHAR) + 1)))
			exit(EXIT_FAILURE);
		ft_strncpy(vasm->labreg->content, vasm->s[i], ft_strichr(vasm->s[i],
					LABEL_CHAR));
		vasm->labreg->content_size = 0;
		vasm->labreg->line = i;
		vasm->labreg->next = NULL;
		tmp = vasm->labreg;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))) ||
				!(tmp->next->content = (char *)malloc(ft_strichr(vasm->s[i],
							LABEL_CHAR) + 1)))
			exit(EXIT_FAILURE);
		tmp = tmp->next;
		ft_strncpy(tmp->content, vasm->s[i], ft_strichr(vasm->s[i], LABEL_CHAR));
		tmp->content_size = 0;
		tmp->line = i;
		tmp->next = NULL;
	}
	return (tmp);
}

t_inst	*store_cmd(t_asm *vasm, t_inst *tmp, char *inst, int i)
{
	int temp;
	if (!vasm->labreg->content)
	{
		if (!(vasm->labreg->content = (char *)malloc(ft_strichr(inst,' ') + 1)))
			exit(EXIT_FAILURE);
		ft_strncpy(vasm->labreg->content, inst, ft_strichr(inst,' '));
		temp = ft_stritabstr(vasm->cmd, vasm->labreg->content, ft_strlen(vasm->labreg->content));
		if (temp == 1 || temp == 9 || temp == 12 || temp == 15)
			vasm->labreg->content_size = 1;
		else
			vasm->labreg->content_size = 2;
		vasm->labreg->line = i;
		vasm->labreg->next = NULL;
		tmp = vasm->labreg;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))) ||
				!(tmp->next->content = (char *)malloc(ft_strichr(inst, ' ') + 1)))
			exit(EXIT_FAILURE);
		tmp = tmp->next;
		ft_strncpy(tmp->content, inst, ft_strichr(inst, ' '));
		temp = ft_stritabstr(vasm->cmd, tmp->content, ft_strlen(tmp->content));
		if (temp == 1 || temp == 9 || temp == 12 || temp == 15)
			tmp->content_size = 1;
		else
			tmp->content_size = 2;
		tmp->line = i;
		tmp->next = NULL;
	}
	return (tmp);
}

t_inst	*store_inst(t_asm *vasm, t_inst *tmp, char *inst, int i)
{
	int j;
	int param;
	int cmd;

	param = ft_strichr_cnt(vasm->s[i], SEPARATOR_CHAR);
	j = 0;
	cmd = ft_stritabstr(vasm->cmd, tmp->content, ft_strlen(tmp->content));
	while (j <= param)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (j < param)
		{
			if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))) ||
					!(tmp->next->content = (char *)malloc(ft_strichr(inst,
								SEPARATOR_CHAR) + 1)))
				exit(EXIT_FAILURE);
			tmp = tmp->next;
			ft_strncpy(tmp->content, inst, ft_strichr(inst, SEPARATOR_CHAR));
			tmp->next = NULL;
		}
		else
		{
			if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))) ||
					!(tmp->next->content = (char *)malloc(ft_strlen(inst) + 1)))
				exit(EXIT_FAILURE);
			tmp = tmp->next;
			ft_strcpy(tmp->content, inst);
			tmp->next = NULL;
		}
		if (inst[0] == 'r')
			tmp->content_size = 1;
		else if (inst[0] == DIRECT_CHAR && inst[1] == LABEL_CHAR)
		{
			if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
				tmp->content_size = 4;
			else
				tmp->content_size = 2;
		}
		else if (inst[0] == DIRECT_CHAR && (ft_isdigit(inst[1]) || (inst[1] ==
						'-' && ft_isdigit(inst[2]))))
		{
			if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
				tmp->content_size = 4;
			else
				tmp->content_size = 2;
		}
		else if (ft_isdigit(inst[0]))
			tmp->content_size = 2;
		tmp->line = i;
		inst = inst + ft_strichr(inst, SEPARATOR_CHAR) + 1;
		++j;
		vasm->cor_size += tmp->content_size;
	}
	return (tmp);
}

void	get_labels(t_asm *vasm)
{
	int i;
	int lbl;
	int comd;
	char *inst;
	t_inst *tmp;

	i = 0;
	vasm->cor_size = 0;
	if (!(vasm->labreg = (t_inst *)malloc(sizeof(t_inst))))
		exit(EXIT_FAILURE);
	vasm->labreg->content = NULL;
	tmp = vasm->labreg;
	while (i < vasm->file_lines)
	{
		if (ft_stristr(vasm->s[i], NAME_CMD_STRING) == -1 &&
			ft_stristr(vasm->s[i], COMMENT_CMD_STRING) == -1 && vasm->s[i][0]
			!= COMMENT_CHAR)
		{
			lbl = 0;
			if (ft_strichr(vasm->s[i], LABEL_CHAR) > 0 && (vasm->s[i]
						[ft_strichr(vasm->s[i], LABEL_CHAR) - 1]) != DIRECT_CHAR)
			{
				lbl = ft_strichr(vasm->s[i], LABEL_CHAR) + 1;
				lbl += ft_trim(vasm->s[i] + lbl);
				tmp = store_label(vasm, tmp, i);
			}
			inst = vasm->s[i] + lbl + ft_trim(vasm->s[i] + lbl);
			tmp = store_cmd(vasm, tmp, inst, i);
			vasm->cor_size += tmp->content_size;
			comd = ft_strichr(inst, ' ') + 1;
			inst += comd;
			tmp = store_inst(vasm, tmp, inst, i);
		}
		++i;
	}
//	tmp = vasm->labreg;
//	while (tmp)
//	{
//		ft_lprintf(1, "content : %s\tsize : %d\n", tmp->content, tmp->content_size);
//		tmp = tmp->next;
//	}
}

