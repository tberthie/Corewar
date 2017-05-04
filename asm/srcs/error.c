/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/04 12:52:51 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		error(t_asm *vasm)
{
	ft_lprintf(2, "ERROR: invalid value in file ");
	ft_lprintf(2, "for %s instruction on line %d\n", vasm->cmd[vasm->command],
			vasm->inst_line + 1);
	exit(EXIT_FAILURE);
}

void		free_all_1(t_asm *vasm)
{
	if (vasm->file_name)
		free(vasm->file_name);
	if (vasm->comment)
		free(vasm->comment);
	if (vasm->name)
		free(vasm->name);
}

void		free_all(t_asm *vasm)
{
	int		i;

	i = 0;
	free_all_1(vasm);
	while (i < vasm->file_lines)
	{
		if (vasm->s[i])
			free(vasm->s[i]);
		++i;
	}
	if (vasm->s)
		free(vasm->s);
	i = 0;
	while (i < 17)
	{
		if (vasm->cmd[i])
			free(vasm->cmd[i]);
		++i;
	}
	if (vasm->cmd)
		free(vasm->cmd);
}
