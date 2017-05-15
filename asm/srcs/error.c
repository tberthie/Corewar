/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 13:32:25 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		error(t_asm *vasm, int err)
{
	if (!err)
	{
		ft_lprintf(2, "Usage : ./asm [-a] <sourcefile.s>\n");
		ft_lprintf(2, "\t-a : Does not create a cor file but display an \n");
		ft_lprintf(2, "annotated version on the standard output\n");
	}
	else if (err == 1)
		ft_lprintf(2, "Champion name missing : .name %cname%c\n", '"', '"');
	else if (err == 2)
		ft_lprintf(2, "Description missing : .comment %ccomment%c\n", '"', '"');
	else if (err == 4)
		ft_lprintf(2, "Champion size is too big !!\n");
	else if (err == 5)
		ft_lprintf(2, "%s file is empty\n", vasm->file);
	else if (err == 6)
		ft_lprintf(2, "Order of commands are not respected\n");
	else
	{
		ft_lprintf(2, "ERROR: invalid value in file ");
		ft_lprintf(2, "for %s instruction on line %d\n",
				vasm->cmd[vasm->command], vasm->inst_line + 1);
	}
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
