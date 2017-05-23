/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:27:15 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/22 17:02:50 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		check_label(t_asm *vasm, t_inst *tmp)
{
	int		size;
	t_inst	*tmp2;

	tmp2 = vasm->labreg;
	size = ft_strlen(tmp->content);
	if (!size || size > T_LAB + 1)
		error(vasm, 3);
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
