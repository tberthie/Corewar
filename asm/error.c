/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/01 17:10:38 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error(t_asm *vasm)
{
	ft_lprintf(2, "ERROR: invalid value in file on line %d\n", vasm->inst_line);
	exit(EXIT_FAILURE);
}


void	free_all(t_asm *vasm)
{
	int i;

	i = 0;
	if (vasm->file)
		free(vasm->file);
	if (vasm->tmp)
		free(vasm->tmp);
	if (vasm->file_name)
		free(vasm->file_name);
	if (vasm->comment)
		free(vasm->comment);
	if (vasm->name)
		free(vasm->name);
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
