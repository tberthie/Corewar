/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 14:52:47 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/09 14:42:51 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_asm(t_asm *vasm)
{
	int line;
	int bytes;
	int size;
	int label;
	t_inst	*tmp;
	t_inst	*tmp2;

	line = 0;
	bytes = 0;
	size = 0;
	label = 0;
	tmp = vasm->labreg;
	tmp2 = tmp;
	while (tmp)
	{
		if (line != (int)tmp->line)
		{
			tmp2 = tmp;
			line = (int)tmp2->line;
			while (tmp2 && line == (int)tmp2->line)
			{
				size += tmp2->content_size;
				tmp2 = tmp2->next;
			}


			tmp2 = tmp;

			if (line == (int)tmp2->line && !tmp2->content_size)
			{
				ft_lprintf(1, "\n\n%d", bytes);
				ft_lprintf(1, "\t:   %s :\n", tmp2->content);
				label = 1;
				tmp2 = tmp2->next;
			}
			if (tmp2 &&line == (int)tmp2->line && tmp2->content_size)
			{
				if (!label)
					ft_lprintf(1, "\n\n%d", bytes);
				else
					ft_lprintf(1, "%d", bytes);
				bytes += size;
				label = 0;
				ft_lprintf(1, "  (%d)\t:\t", size);
			}
			size = 0;
			while (tmp2 && line == (int)tmp2->line)
			{
				if (!tmp2->content_size)
					ft_lprintf(1, "\t\t%s:\n", tmp2->content);
				else
					ft_lprintf(1, "%s\t\t", tmp2->content);
				tmp2 = tmp2->next;
			}
//			ft_lprintf(1, "\n\t");
//		}
			tmp2 = tmp;
//		if (line != (int)tmp->line)
//		{
//			line = (int)tmp->line;
//			ft_lprintf(1, "%s\n", vasm->s[line]);
//		}
			while (tmp2 && line == (int)tmp2->line)
			{
//				ft_lprintf(1, "content[0] : %c\n", tmp2->content[0]);
				if (tmp2->content_size)
				{
					ft_lprintf(1, "\t");
					if (tmp2->content[0] == 'r')
					{
						print_reg(tmp2);
//						ft_lprintf(1, "reg OK\n");
					}
					else if (ft_nisdigit(tmp2->content, ft_strlen(tmp2->content)))
					{
//						ft_lprintf(1, "Je rentre dans le ind\n");
						print_ind(vasm, tmp2, 0);
					}
					else if (tmp2->content[0] == DIRECT_CHAR)
					{
//						ft_lprintf(1, "Je rentre dans le dir\n");
						print_dir(vasm, tmp2, 0, 0);
					}
					else
					{
//						ft_lprintf(1, "Je rentre dans le cmd\n");
						vasm->command = ft_stritabstr(vasm->cmd, tmp2->content,
								ft_strlen(tmp2->content));
						vasm->instruct = tmp;
						if (vasm->command >= 0)
						{
							print_cmd(vasm, tmp2);
						}
					}
				}
				tmp2 = tmp2->next;
//			ft_lprintf(1, "\n");
			}
		}
		if (tmp->content_size)
		{
			ft_lprintf(1, "\t");
			if (tmp->content[0] == 'r')
				print_reg(tmp);
			else if (ft_nisdigit(tmp->content, ft_strlen(tmp->content)))
				print_ind_int(vasm, tmp, 0);
			else if (tmp->content[0] == DIRECT_CHAR)
				print_dir_int(vasm, tmp, 0);
			else
			{
				vasm->command = ft_stritabstr(vasm->cmd, tmp->content,
						ft_strlen(tmp->content));
				vasm->instruct = tmp;
				if (vasm->command >= 0)
				{
					print_cmd(vasm, tmp);
				}
			}
//			ft_lprintf(1, "\n");
		}
		tmp = tmp->next;
	}
}

void		print_hex(t_asm *vasm, char *str)
{
	vasm->s = ft_strsplit(str, '\n');
//	ft_lprintf(1, "BB\n");
	vasm->file_lines = ft_ptrlen(vasm->s);
	get_labels(vasm, -1, 0, NULL);
//	ft_lprintf(1, "CC\n");
	init_checktab(vasm);
	check_asm(vasm, 0, NULL);
//	ft_lprintf(1, "DD\n");
	get_cor_size(vasm);
//	ft_lprintf(1, "EE\n");
//	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0600)) == -1)
//		exit(EXIT_FAILURE);
//	ft_lprintf(1, "FF\n");
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
//	if (!(vasm->file_name = (char *)malloc(ft_strlen(str) + 3)))
//		exit(EXIT_FAILURE);
//	ft_strncpy(vasm->file_name, str, ft_strlen(str) - 1);
//	vasm->file_name = ft_strcat(vasm->file_name, "cor");
	if (!(tmp = ft_parse(str)))
		exit(EXIT_FAILURE);
//	ft_putendl(tmp);
	init_cmd(vasm);
//	ft_lprintf(1, "AA\n");
	print_hex(vasm, tmp);
	if (tmp)
		free(tmp);
}
