/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 11:33:22 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 13:53:54 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_inst		*store_str(t_asm *vasm, t_inst *tmp, int i, char *inst)
{
	int size;

	if (inst[0] == '"')
		size = ft_strichr_last(inst, '"') + 1;
	else if (inst[0] == ',')
		size = 1;
	else if (inst[0] == COMMENT_CHAR)
		size = 0;
	else if (ft_strichr(inst, COMMENT_CHAR) > 0 && ft_strichr(inst, COMMENT_CHAR) < get_iword(inst))
		size = ft_strichr(inst, COMMENT_CHAR);
	else
		size = get_iword(inst);
//	ft_lprintf(1, "inst : %s\nsize : %d\n", inst, size);
	if (size && !vasm->labreg->content)
	{
		first_node(vasm, i, size);
		ft_strncpy(vasm->labreg->content, inst, size);
		tmp = vasm->labreg;
	}
	else if (size)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		tmp = other_node(tmp->next, i, size);
		ft_strncpy(tmp->content, inst, size);
	}
	return (tmp);
}

void		get_str(t_asm *vasm, int i, char *inst)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (i < vasm->file_lines)
	{
//		ft_lprintf(1, "s[i] : %s\n", vasm->s[i]);
		inst = vasm->s[i] + ft_trim(vasm->s[i]);
		while (inst[0] != '\0')
		{
			tmp = store_str(vasm, tmp, i, inst);
			if (inst[0] == '"')
				inst += ft_strichr_last(inst, '"') + 1;
			else if (inst[0] == ',')
				inst += 1;
			else if (inst[0] == COMMENT_CHAR)
				inst += ft_strlen(inst);
			else if (ft_strichr(inst, COMMENT_CHAR) > 0 && ft_strichr(inst, COMMENT_CHAR) < get_iword(inst))
				inst += ft_strichr(inst, COMMENT_CHAR);
			else
				inst += get_iword(inst);
			inst += ft_trim(inst);
		}
		++i;
	}
}

t_inst		*get_first_inst(t_inst *tmp)
{
	while (tmp && (tmp->content[0] == '.' || tmp->content[0] == '"'))/*ft_strintabstr(vasm->cmd, tmp->content,
			ft_strlen(tmp->content)) == -1)*/
		tmp = tmp->next;
	return (tmp);
}
