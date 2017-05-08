/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:39:42 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		free_all(t_asm *vasm)
{
	int		i;

	if (vasm->file_name)
		free(vasm->file_name);
	if (vasm->comment)
		free(vasm->comment);
	if (vasm->name)
		free(vasm->name);
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
