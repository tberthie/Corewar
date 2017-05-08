/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 14:52:47 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/08 13:31:59 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_asm(t_asm *vasm)
{
	int line;
	t_inst	*tmp;
	t_inst	*tmp2;

	line = 0;
	tmp = vasm->labreg;
	tmp2 = tmp;
	while (tmp)
	{

		if (line != (int)tmp->line)
		{
			tmp2 = tmp;
			line = (int)tmp2->line;
			while (line == (int)tmp2->line && tmp2)
			{
				if (!tmp2->content_size)
					ft_lprintf(1, "%s :\n", tmp2->content);
				else
					ft_lprintf(1, "%s\t", tmp2->content);
				tmp2 = tmp2->next;
			}
			ft_lprintf(1, "\n");
		}
//		if (line != (int)tmp->line)
//		{
//			line = (int)tmp->line;
//			ft_lprintf(1, "%s\n", vasm->s[line]);
//		}
		if (tmp->content_size)
		{
			if (tmp->content[0] == 'r')
				print_reg(tmp);
			else if (ft_nisdigit(tmp->content, ft_strlen(tmp->content)))
				print_ind(vasm, tmp, 0);
			else if (tmp->content[0] == DIRECT_CHAR)
				print_dir(vasm, tmp, 0, 0);
			else
			{
				vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
						ft_strlen(tmp->content));
				vasm->instruct = tmp;
				if (vasm->command >= 0)
				{
					ft_lprintf(1, "\n");
					print_cmd(vasm, tmp);
				}
			}
		}
		tmp = tmp->next;
	}
}

void		print_hex(t_asm *vasm, char *str)
{
	vasm->s = ft_strsplit(str, '\n');
	vasm->file_lines = ft_ptrlen(vasm->s);
	get_labels(vasm, -1, 0, NULL);
	init_checktab(vasm);
	check_asm(vasm, 0, NULL);
	get_cor_size(vasm);
	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0600)) == -1)
		exit(EXIT_FAILURE);
	get_header(vasm);
	ft_lprintf(1, "Dumping annotated program on standard output\n");
	ft_lprintf(1, "Program size : %d bytes\n", vasm->cor_size);
	print_header(vasm, 0);
	print_asm(vasm);
	close(vasm->fd);
	free_all(vasm);
}

void		aff_parse(t_asm *vasm, char *str)
{
	char	*tmp;

	init_asm(vasm);
	if (!(vasm->file_name = (char *)malloc(ft_strlen(str) + 3)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->file_name, str, ft_strlen(str) - 1);
	vasm->file_name = ft_strcat(vasm->file_name, "cor");
	if (!(tmp = ft_parse(str)))
		exit(EXIT_FAILURE);
	init_cmd(vasm);
	print_hex(vasm, tmp);
	if (tmp)
		free(tmp);
}
