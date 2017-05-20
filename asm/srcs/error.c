/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/20 13:33:09 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		error_1(t_asm *vasm, int err)
{
	if (err == 7)
		ft_lprintf(2, "No instructions in %s\n", vasm->file);
	else if (err == 8)
		ft_lprintf(2, "Any instructions must be on the same line\n");
	else if (err == 9)
		ft_lprintf(2, "Champion name must be on one line : .name %cabc%c\n",
				'"', '"');
	else if (err == 10)
		ft_lprintf(2, "Description must be on one line : .comment %cdef%c\n",
				'"', '"');
	else if (err == 11)
		ft_lprintf(2, "Error : duplicate label at line %d\n", vasm->inst_line);
}

void		error(t_asm *vasm, int err)
{
	if (!err)
	{
		ft_lprintf(2, "Usage : ./asm [-a] <sourcefile.s>\n");
		ft_lprintf(2, "\t-a : Does not create a cor file but display an \n");
		ft_lprintf(2, "annotated version on the standard output\n");
	}
	else if (err == 1)
		ft_lprintf(2, "Champion name missing : .name %cabc%c\n", '"', '"');
	else if (err == 2)
		ft_lprintf(2, "Description missing : .comment %cdef%c\n", '"', '"');
	else if (err == 3)
	{
		ft_lprintf(2, "ERROR: invalid value in file ");
		ft_lprintf(2, "for %s instruction on line %d\n",
				vasm->cmd[vasm->command], vasm->inst_line);
	}
	else if (err == 4)
		ft_lprintf(2, "Champion size is too big !!\n");
	else if (err == 5)
		ft_lprintf(2, "%s file is empty\n", vasm->file);
	else if (err == 6)
		ft_lprintf(2, "Order of commands are not respected\n");
	else
		error_1(vasm, err);
	exit(EXIT_FAILURE);
}

void		free_list(t_asm *vasm)
{
	t_inst *tmp;
	t_inst *tmp2;

	tmp = vasm->labreg;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp->content);
		tmp->content = NULL;
		tmp = tmp->next;
		free(tmp2);
	}
}

void		free_all_1(t_asm *vasm)
{
	if (vasm->file_name)
		free(vasm->file_name);
	if (vasm->comment)
		free(vasm->comment);
	if (vasm->name)
		free(vasm->name);
	free_list(vasm);
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
	if (vasm->cmd)
	{
		i = ft_ptrlen(vasm->cmd);
		while (i >= 0)
		{
			free(vasm->cmd[i]);
			--i;
		}
	}
	if (vasm->cmd)
		free(vasm->cmd);
}
