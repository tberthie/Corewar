/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/19 11:58:26 by gthomas          ###   ########.fr       */
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
	else if (err == 12)
		ft_lprintf(2, "Champion name must be : .name %cname%c\n", '"', '"');
	else if (err == 13)
		ft_lprintf(2, "Description must be : .comment %cdesc%c\n", '"', '"');
	else if (err == 14)
		ft_lprintf(2, "Champion name is too long\n");
	else if (err == 15)
		ft_lprintf(2, "Description is too long\n");
	else if (err == 16)
		ft_lprintf(2, "Duplicate .name or .comment\n");
	else if (err == 17)
		ft_lprintf(2, "Name or Comment cannot be empty\n");
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
		ft_lprintf(2, "on line %d\n", vasm->inst_line);
	}
	else if (err == 4)
		ft_lprintf(2, "Champion size is too big !!\n");
	else if (err == 5)
		ft_lprintf(2, "%s file is empty\n", vasm->file);
	else if (err == 6)
		ft_lprintf(2, "Order of commands is not respected\n");
	else
		error_1(vasm, err);
	exit(EXIT_FAILURE);
}

void		cor_usage(t_asm *vasm, char *av)
{
	int		len;
	int		ext;

	ext = ft_stristr(av, ".s");
	len = ft_strlen(av);
	if (ext == -1 || ext != len - 2 || len < 3 ||
			ft_strichr_cnt(av, '.') != 1 || ft_strichr_last(av, '/') ==
			ft_strichr(av, '.') - 1)
		error(vasm, 0);
}
