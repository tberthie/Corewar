/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 11:33:22 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/19 11:57:20 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ret_size(char *inst)
{
	int		size;

	if (inst[0] == '"')
		size = ft_strichr_last(inst, '"') + 1;
	else if (inst[0] == ',')
		size = 1;
	else if (inst[0] == COMMENT_CHAR)
		size = 0;
	else if (ft_strichr(inst, COMMENT_CHAR) > 0 && ft_strichr(inst,
			COMMENT_CHAR) < get_iword(inst))
		size = ft_strichr(inst, COMMENT_CHAR);
	else
		size = get_iword(inst);
	return (size);
}

t_inst		*store_str(t_asm *vasm, t_inst *tmp, int i)
{
	int size;

	size = ret_size(vasm->tmp);
	if (size && !vasm->labreg)
	{
		first_node(vasm, i, size);
		ft_strncpy(vasm->labreg->content, vasm->tmp, size);
		tmp = vasm->labreg;
	}
	else if (size)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		tmp = other_node(tmp->next, i, size);
		ft_strncpy(tmp->content, vasm->tmp, size);
	}
	return (tmp);
}

void		get_str(t_asm *vasm, int i)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (i < vasm->file_lines)
	{
		vasm->tmp = vasm->s[i] + ft_trim(vasm->s[i]);
		while (vasm->tmp[0] > '\0' && vasm->tmp[0] != COMMENT_CHAR)
		{
			tmp = store_str(vasm, tmp, i);
			if (vasm->tmp[0] == '"')
				vasm->tmp += ft_strichr_last(vasm->tmp, '"') + 1;
			else if (vasm->tmp[0] == ',')
				vasm->tmp += 1;
			else if (vasm->tmp[0] == COMMENT_CHAR)
				vasm->tmp += ft_strlen(vasm->tmp);
			else if (ft_strichr(vasm->tmp, COMMENT_CHAR) > 0 &&
					ft_strichr(vasm->tmp, COMMENT_CHAR) < get_iword(vasm->tmp))
				vasm->tmp += ft_strichr(vasm->tmp, COMMENT_CHAR);
			else
				vasm->tmp += get_iword(vasm->tmp);
			vasm->tmp += ft_trim(vasm->tmp);
		}
		++i;
	}
}

t_inst		*get_first_inst(t_inst *tmp)
{
	while (tmp && tmp->content &&
			(tmp->content[0] == '.' || tmp->content[0] == '"'))
		tmp = tmp->next;
	return (tmp);
}
