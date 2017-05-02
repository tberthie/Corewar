/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:15:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/02 18:11:31 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_ocp(t_inst *node, int param, int oct, int i)
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

void	print_hex(t_asm *vasm, char *str)
{
	vasm->s = ft_strsplit(str, '\n');
	vasm->file_lines = ft_ptrlen(vasm->s);
	get_labels(vasm, -1, 0, NULL);
	check_asm(vasm, 0, NULL);
	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0600)) == -1)
		exit(EXIT_FAILURE);
	get_cor_size(vasm);
	get_header(vasm);
	put_header(vasm, 0);
	put_asm(vasm);
	close(vasm->fd);
	free_all(vasm);
}

void	parse(t_asm *vasm, char *str)
{
	char *tmp;

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

int		main(int ac, char **av)
{
	t_asm vasm;

	vasm.zero = 0;
	vasm.ff = 255;
	if (ac == 2 && av[1])
	{
		if (ft_stristr(av[1], ".s") == -1)
			return (-1);
		vasm.file = av[1];
		parse(&vasm, av[1]);
	}
	return (0);
}
