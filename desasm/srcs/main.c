/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:15:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/04 16:47:44 by gthomas          ###   ########.fr       */
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

void		put_asm(t_asm *vasm)
{
	t_inst *tmp;

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

void	get_magic_number(t_asm *vasm, char *str)
{
	vasm->magic = str[3] & 0x000000ff;
	vasm->magic += (str[2] * 0xff) & 0x0000ff00;
	vasm->magic += (str[1] * 0xffff) & 0x00ff0000;
	vasm->magic += (str[0] * 0xffffff) & 0xff000000;
	ft_lprintf(1, "\nmagic = %x\n", vasm->magic);
}

void	get_name(t_asm *vasm, char *str)
{
	int i;

	i = 4;
	if (!(vasm->name = (char *)malloc(ft_strlen(str + i) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->name, str + i, ft_strlen(str + i));
	ft_lprintf(1, "name : %s\n", vasm->name);
}

void	get_prog_size(t_asm *vasm, char *str)
{
	vasm->cor_size = str[PROG_NAME_LENGTH + 11] & 0x000000ff;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 10] * 0xff) & 0x0000ff00;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 9] * 0xffff) & 0x00ff0000;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 8] * 0xffffff) & 0xff000000;
	ft_lprintf(1, "\ncor size = %d\n", vasm->cor_size);
}

void	get_comment(t_asm *vasm, char *str)
{
	int begin;

	begin = 12 + PROG_NAME_LENGTH;
	if (!(vasm->comment = (char *)malloc(ft_strlen(str + begin) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->comment, str + begin, ft_strlen(str + begin));
	ft_lprintf(1, "comment : %s\n", vasm->comment);
}

void	print_hex(t_asm *vasm, char *str, int nb)
{
	int i;

	get_magic_number(vasm, str);
	get_name(vasm, str);
	get_prog_size(vasm, str);
	get_comment(vasm, str);
	i = 4;
	nb = 4;
	while (str[i])
	{
		ft_lprintf(1, "%x", str[i]);
		++i;
	}

//	vasm->s = ft_strsplit(str, '\n');
//	vasm->file_lines = ft_ptrlen(vasm->s);
//	get_labels(vasm, -1, 0, NULL);
//	check_asm(vasm, 0, NULL);
	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0666)) == -1)
		exit(EXIT_FAILURE);
//	get_cor_size(vasm);
//	get_header(vasm);
//	put_header(vasm, 0);
//	put_asm(vasm);
	close(vasm->fd);
	free_all(vasm);
}

void	parse(t_asm *vasm, char *str)
{
	char *tmp;
	char buf[4096];
	int fd;
	int nb;
	int ret;
	int i;
	int j;

	nb = 0;
	i = 0;
	j = 0;
	init_asm(vasm);
	ft_putendl(str);
	if (!(tmp = malloc(1)))
		exit(EXIT_FAILURE);
	tmp[0] = '\0';
	if (!(vasm->file_name = (char *)malloc(ft_strlen(str) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->file_name, str, ft_strlen(str) - 3);
	vasm->file_name = ft_strcat(vasm->file_name, "s");
	ft_putendl(vasm->file_name);
	chmod(str, 0666);
	if ((fd = open(str, O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	while ((ret = read(fd, buf, 4095)))
	{
		ft_realloc(&tmp, ret);
		while (i < ret)
		{
			tmp[j] = buf[i];
			ft_putchar(tmp[j]);
			++i;
			++j;
		}
		i = 0;
		nb += ret;
	}
//	if (!(tmp = ft_parse(str)))
//	{
//		ft_putendl("marche po !!");
//		exit(EXIT_FAILURE);
//	}
	ft_putendl("toto");
//	ft_putendl(tmp);
	init_cmd(vasm);
	print_hex(vasm, tmp, nb);
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
		if (ft_stristr(av[1], ".cor") == -1)
			return (-1);
		vasm.file = av[1];
		parse(&vasm, av[1]);
	}
	return (0);
}
