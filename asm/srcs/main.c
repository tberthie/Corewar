/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:15:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:44:45 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			find_ocp(t_inst *node, int param, int oct, int i)
{
	param = node->line;
	node = node->next;
	while (node && (int)node->line == param)
	{
		oct *= 4;
		if (node->content[0] == 'r')
			oct += 1;
		else if (node->content[0] == '%')
			oct += 2;
		else if (ft_nisdigit(node->content, ft_strlen(node->content)))
			oct += 3;
		node = node->next;
		++i;
	}
	while (i < 4)
	{
		oct *= 4;
		++i;
	}
	return (oct);
}

void		put_asm(t_asm *vasm)
{
	t_inst	*tmp;

	tmp = vasm->labreg;
	while (tmp)
	{
		if (tmp->content_size)
		{
			if (tmp->content[0] == 'r')
				put_reg(vasm, tmp);
			else if (ft_nisdigit(tmp->content, ft_strlen(tmp->content)))
				put_ind(vasm, tmp, 0);
			else if (tmp->content[0] == DIRECT_CHAR)
				put_dir(vasm, tmp, 0, 0);
			else
			{
				vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
						ft_strlen(tmp->content));
				vasm->instruct = tmp;
				if (vasm->command >= 0)
					put_cmd(vasm, tmp);
			}
		}
		tmp = tmp->next;
	}
}

void		cor_hex(t_asm *vasm, char *str)
{
	vasm->s = ft_strsplit(str, '\n');
	vasm->file_lines = ft_ptrlen(vasm->s);
	get_labels(vasm, -1, 0, NULL);
	init_checktab(vasm);
	check_asm(vasm, 0, vasm->tmp);
	get_cor_size(vasm);
	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0600)) == -1)
		exit(EXIT_FAILURE);
	ft_lprintf(1, "Writing output program to %s\n", vasm->file_name);
	put_header(vasm);
	put_asm(vasm);
	close(vasm->fd);
	free_all(vasm);
}

void		parse(t_asm *vasm, char *str)
{
	char	*tmp;

	init_asm(vasm);
	if (!(vasm->file_name = (char *)malloc(ft_strlen(str) + 3)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->file_name, str, ft_strlen(str) - 1);
	vasm->file_name = ft_strcat(vasm->file_name, "cor");
	if (!(tmp = ft_parse(str)))
		error(vasm, 5);
	init_cmd(vasm);
	cor_hex(vasm, tmp);
	if (tmp)
		free(tmp);
}

int			main(int ac, char **av)
{
	t_asm	*vasm;

	if (!(vasm = (t_asm *)malloc(sizeof(t_asm))))
		exit(EXIT_FAILURE);
	vasm->zero = 0;
	vasm->ff = 255;
	if (ac == 2)
	{
		if (ft_stristr(av[1], ".s") == -1)
			error(vasm, 0);
		vasm->file = av[1];
		parse(vasm, av[1]);
	}
	else if (ac == 3)
	{
		if (ft_strcmp(av[1], "-a"))
			error(vasm, 0);
		if (ft_stristr(av[2], ".s") == -1)
			error(vasm, 0);
		vasm->file = av[2];
		aff_parse(vasm, av[2]);
	}
	return (0);
}
