/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:15:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/02 11:41:00 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_ocp(t_inst *node)
{
	int param;
	int oct;
	int i;

	param = node->line;
	node = node->next;
	oct = 0;
	i = 0;
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

void	check_label(t_asm *vasm, int i)
{
	int j;
	int size;

	j = 0;
	size = ft_strichr(vasm->s[i], LABEL_CHAR);
	if (!size || size > T_LAB + 1)
		error(vasm);
	while (j < size)
	{
		if (ft_strichr(LABEL_CHARS, vasm->s[i][j]) == -1)
			error(vasm);
		++j;
	}
}

void	check_header(t_asm *vasm, int i)
{
	if (!ft_strncmp(vasm->s[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) ||
			!ft_strncmp(vasm->s[i], COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
	{
		if (ft_strichr_cnt(vasm->s[i], '"') != 2)
			error(vasm);
		if (ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i], '"') == 1)
			error(vasm);
		if (vasm->s[i][ft_strichr_last(vasm->s[i], '"') + 1] != '\0')
			error(vasm);
	}
	else
		error(vasm);
}

void	check_asm(t_asm *vasm)
{
	int i;
	char *inst;

	i = 0;
	init_checktab(vasm);
	while (i < vasm->file_lines)
	{
		if (ft_stristr(vasm->s[i], NAME_CMD_STRING) == -1 &&
				ft_stristr(vasm->s[i], COMMENT_CMD_STRING) == -1 && vasm->s[i][0] != COMMENT_CHAR)
		{
			vasm->inst_line = i;
			inst = vasm->s[i];
			if (ft_strichr(vasm->s[i], LABEL_CHAR) != -1 &&
					vasm->s[i][ft_strichr(vasm->s[i], LABEL_CHAR) + 1] == ' ')
			{
				check_label(vasm, i);
				inst = vasm->s[i] + ft_strichr(vasm->s[i], LABEL_CHAR) + 1;
				inst += ft_trim(inst);
			}
			vasm->checktab[ft_stritabstr(vasm->cmd, inst, ft_strichr(inst,
						' '))](vasm, inst + ft_strichr(inst, ' ') + 1);
		}
		else if (vasm->s[i][0] != COMMENT_CHAR && (!ft_stristr(vasm->s[i],
			NAME_CMD_STRING) || !ft_stristr(vasm->s[i], COMMENT_CMD_STRING)))
			check_header(vasm, i);
		++i;
	}
}

void	get_header(t_asm *vasm)
{
	int	tmp;

	tmp = ft_stritabstr(vasm->s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	if (!(vasm->name = (char *)malloc(PROG_NAME_LENGTH + 1)))
		exit(EXIT_FAILURE);
	ft_bzero(vasm->name, PROG_NAME_LENGTH + 1);
	ft_strncpy(vasm->name, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1, ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"') - 1);
	tmp = ft_stritabstr(vasm->s, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING));
	if (!(vasm->comment = (char *)malloc(COMMENT_LENGTH + 1)))
		exit(EXIT_FAILURE);
	ft_bzero(vasm->comment, COMMENT_LENGTH + 1);
	ft_strncpy(vasm->comment, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1, ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"') - 1);
}

void	put_four_zero(t_asm *vasm)
{
	write(vasm->fd, &vasm->zero, 1);
	write(vasm->fd, &vasm->zero, 1);
	write(vasm->fd, &vasm->zero, 1);
	write(vasm->fd, &vasm->zero, 1);
}

void	put_magic(t_asm *vasm)
{
	int i;
	char magic_nb[4];

	i = 3;
	magic_nb[0] = COREWAR_EXEC_MAGIC & 0x000000ff;
	magic_nb[1] = (COREWAR_EXEC_MAGIC & 0x0000ff00) >> 8;
	magic_nb[2] = (COREWAR_EXEC_MAGIC & 0x00ff0000) >> 16;
	magic_nb[3] = (COREWAR_EXEC_MAGIC & 0xff000000) >> 24;
	while (i >= 0)
	{
		write(vasm->fd, &magic_nb[i], 1);
		--i;
	}
}

void	put_header(t_asm *vasm)
{
	int i;
	char cor[4];

	cor[0] = 0;
	cor[1] = 0;
	cor[2] = 0;
	cor[3] = 0;
	if (vasm->cor_size > 65535)
		cor[1] = (vasm->cor_size & 0x00ff0000) >> 16;
	else if (vasm->cor_size > 255)
		cor[2] = (vasm->cor_size & 0x0000ff00) >> 8;
	cor[3] = (vasm->cor_size & 0x000000ff);
	put_magic(vasm);
	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		write(vasm->fd, &vasm->name[i], 1);
		++i;
	}
	i = 0;
	put_four_zero(vasm);
	write(vasm->fd, &cor, 4);
	while (i < COMMENT_LENGTH)
	{
		write(vasm->fd, &vasm->comment[i], 1);
		++i;
	}
	put_four_zero(vasm);
}

void	print_hex(t_asm *vasm, char *str)
{
	vasm->s = ft_strsplit(str, '\n');
	vasm->file_lines = ft_ptrlen(vasm->s);
	if (str)
		free(str);
	get_labels(vasm);
	check_asm(vasm);
	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0600)) == -1)
		exit(EXIT_FAILURE);
	get_header(vasm);
	put_header(vasm);
	put_asm(vasm);
	close(vasm->fd);
	free_all(vasm);
}

void	parse(t_asm *vasm, char *str)
{
	char *tmp;

	if (!(vasm->file_name = (char *)malloc(ft_strlen(str) + 3)))
		exit(EXIT_FAILURE);
	//	ft_strcpy(vasm->file_name + ft_stristr(cor, ".s") + 1, "cor");
	ft_strcpy(vasm->file_name, "toto.cor");
	tmp = ft_parse(str);
	init_cmd(vasm);
	print_hex(vasm, tmp);
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
