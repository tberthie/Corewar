/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:48:56 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:39:48 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		init_asm(t_asm *vasm)
{
	vasm->cmd = NULL;
	vasm->name = NULL;
	vasm->comment = NULL;
	vasm->file_name = NULL;
}

static void	alloc_cmd(t_asm *vasm)
{
	int		i;

	i = 0;
	if (!(vasm->cmd = (char **)malloc(17 * sizeof(char *))))
		exit(EXIT_FAILURE);
	while (i < 17)
	{
		if (!(vasm->cmd[i] = (char *)malloc(5)))
			exit(EXIT_FAILURE);
		++i;
	}
}

void		init_cmd(t_asm *vasm)
{
	alloc_cmd(vasm);
	ft_strcpy(vasm->cmd[0], "0");
	ft_strcpy(vasm->cmd[1], "live");
	ft_strcpy(vasm->cmd[2], "ld");
	ft_strcpy(vasm->cmd[3], "st");
	ft_strcpy(vasm->cmd[4], "add");
	ft_strcpy(vasm->cmd[5], "sub");
	ft_strcpy(vasm->cmd[6], "and");
	ft_strcpy(vasm->cmd[7], "or");
	ft_strcpy(vasm->cmd[8], "xor");
	ft_strcpy(vasm->cmd[9], "zjmp");
	ft_strcpy(vasm->cmd[10], "ldi");
	ft_strcpy(vasm->cmd[11], "sti");
	ft_strcpy(vasm->cmd[12], "fork");
	ft_strcpy(vasm->cmd[13], "lld");
	ft_strcpy(vasm->cmd[14], "lldi");
	ft_strcpy(vasm->cmd[15], "lfork");
	ft_strcpy(vasm->cmd[16], "aff");
}
