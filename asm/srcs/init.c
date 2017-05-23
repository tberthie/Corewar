/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:48:56 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 14:31:37 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		init_asm(t_asm *vasm)
{
	vasm->cmd = NULL;
	vasm->s = NULL;
	vasm->name = NULL;
	vasm->comment = NULL;
	vasm->file_name = NULL;
	vasm->instruct = NULL;
	if (!(vasm->labreg = (t_inst *)malloc(sizeof(t_inst))))
		exit(EXIT_FAILURE);
	vasm->labreg->content = NULL;
	vasm->inst_line = 0;
	vasm->bytes = 0;
	vasm->size = 0;
	vasm->cor_size = 0;
	vasm->command = 0;
	vasm->n = 0;
	vasm->c = 0;
}

void		init_checktab(t_asm *vasm)
{
	vasm->checktab[0] = &check_none;
	vasm->checktab[1] = &check_live;
	vasm->checktab[2] = &check_ld;
	vasm->checktab[3] = &check_st;
	vasm->checktab[4] = &check_add;
	vasm->checktab[5] = &check_sub;
	vasm->checktab[6] = &check_and;
	vasm->checktab[7] = &check_or;
	vasm->checktab[8] = &check_xor;
	vasm->checktab[9] = &check_zjmp;
	vasm->checktab[10] = &check_ldi;
	vasm->checktab[11] = &check_sti;
	vasm->checktab[12] = &check_fork;
	vasm->checktab[13] = &check_lld;
	vasm->checktab[14] = &check_lldi;
	vasm->checktab[15] = &check_lfork;
	vasm->checktab[16] = &check_aff;
	vasm->inst_line = -1;
}

static void	alloc_cmd(t_asm *vasm)
{
	int		i;

	i = 0;
	if (!(vasm->cmd = (char **)malloc(17 * sizeof(char *))))
		exit(EXIT_FAILURE);
	while (i < 17)
	{
		if (!(vasm->cmd[i] = (char *)malloc(6)))
			exit(EXIT_FAILURE);
		ft_bzero(vasm->cmd[i], 6);
		++i;
	}
}

void		init_icmd(t_asm *vasm)
{
	vasm->icmd[0] = 0;
	vasm->icmd[1] = 1;
	vasm->icmd[2] = 3;
	vasm->icmd[3] = 3;
	vasm->icmd[4] = 5;
	vasm->icmd[5] = 5;
	vasm->icmd[6] = 5;
	vasm->icmd[7] = 5;
	vasm->icmd[8] = 5;
	vasm->icmd[9] = 1;
	vasm->icmd[10] = 5;
	vasm->icmd[11] = 5;
	vasm->icmd[12] = 1;
	vasm->icmd[13] = 3;
	vasm->icmd[14] = 5;
	vasm->icmd[15] = 1;
	vasm->icmd[16] = 1;
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
	vasm->cmd[17] = NULL;
	init_icmd(vasm);
}
