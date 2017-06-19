/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:52:18 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/19 11:57:08 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			ft_lstntabstr(t_inst **begin, char *str, int size, int nb)
{
	t_inst	*tmp;

	tmp = *begin;
	while (tmp)
	{
		size = ft_strlen(tmp->content) - 1;
		if (size == 0)
			size = 1;
		if ((int)ft_strlen(str) == size &&
				!ft_strncmp(tmp->content, str, size) && nb ==
				(int)tmp->content_size)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		first_node(t_asm *vasm, int i, int size)
{
	if (!(vasm->labreg = (t_inst *)malloc(sizeof(t_inst))))
		exit(EXIT_FAILURE);
	if (!(vasm->labreg->content = (char *)malloc(size + 1)))
		exit(EXIT_FAILURE);
	vasm->labreg->content_size = 0;
	vasm->labreg->line = i + 1;
	vasm->labreg->next = NULL;
}

t_inst		*other_node(t_inst *tmp, int i, int size)
{
	if (!(tmp->content = (char *)malloc(size + 1)))
		exit(EXIT_FAILURE);
	tmp->content_size = 0;
	tmp->line = i + 1;
	tmp->next = NULL;
	return (tmp);
}

void		store_regdirind(t_asm *vasm, t_inst *tmp, int i, char *inst)
{
	int		cmd;

	i = 0;
	cmd = vasm->command;
	if (inst[0] == 'r' && ft_strichr(inst, LABEL_CHAR) == -1)
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
	else if (!ft_strichr(inst, LABEL_CHAR) ||
			(ft_strichr(inst, LABEL_CHAR) == -1 && (ft_isdigit(inst[0]) ||
			(inst[0] == '-' && ft_isdigit(inst[1])))))
		tmp->content_size = 2;
}

void		get_cor_size(t_asm *vasm)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	if (!tmp)
		vasm->cor_size = 0;
	while (tmp)
	{
		vasm->cor_size += tmp->content_size;
		tmp = tmp->next;
	}
	if (vasm->cor_size > CHAMP_MAX_SIZE)
		error(vasm, 4);
}
