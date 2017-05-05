/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:15:16 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/05 16:42:41 by gthomas          ###   ########.fr       */
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
	if (vasm->magic != COREWAR_EXEC_MAGIC)
		error(vasm);
}

void	get_name(t_asm *vasm, char *str)
{
	int i;

	i = 4;
	if (!(vasm->name = (char *)malloc(ft_strlen(str + i) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->name, str + i, ft_strlen(str + i));
	ft_lprintf(1, "name : %s\n", vasm->name);
	ft_lprintf(vasm->fd, ".name %c%s%c\n", '"', vasm->name, '"');
}

void	get_prog_size(t_asm *vasm, char *str)
{
	vasm->cor_size = str[PROG_NAME_LENGTH + 11] & 0x000000ff;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 10] * 0xff) & 0x0000ff00;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 9] * 0xffff) & 0x00ff0000;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 8] * 0xffffff) & 0xff000000;
	ft_lprintf(1, "cor size = %d\n", vasm->cor_size);
}

void	get_comment(t_asm *vasm, char *str)
{
	int begin;

	begin = 12 + PROG_NAME_LENGTH;
	if (!(vasm->comment = (char *)malloc(ft_strlen(str + begin) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->comment, str + begin, ft_strlen(str + begin));
	ft_lprintf(1, "comment : %s\n", vasm->comment);
	ft_lprintf(vasm->fd, ".comment %c%s%c\n", '"', vasm->comment, '"');
}

void	print_hex(t_asm *vasm, char *str, int nb)
{
	int i;
	int cmd;

	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0666)) == -1)
		exit(EXIT_FAILURE);
	get_magic_number(vasm, str);
	get_name(vasm, str);
	get_prog_size(vasm, str);
	get_comment(vasm, str);
	i = 12 + PROG_NAME_LENGTH;
	while (str[i])
		++i;
	while (!str[i])
		++i;
	ft_lprintf(1, "begin cor : %d\t%x\n", i, i);

	//	nb = 4;
	//	while (str[i])
	//	{
	//		ft_lprintf(1, "%x", str[i]);
	//		++i;
	//	}

	//	vasm->s = ft_strsplit(str, '\n');
	//	vasm->file_lines = ft_ptrlen(vasm->s);
	//	get_labels(vasm, -1, 0, NULL);
	//	check_asm(vasm, 0, NULL);

	while (i < nb)
	{
		vasm->ocp = 0;
		if (str[i] > 0 && str[i] < 17)
		{
			cmd = (int)str[i];
			ft_lprintf(vasm->fd, "%s ", vasm->cmd[(int)str[i]]);
			ft_lprintf(1, "%d %x\n", i, cmd);
//			ft_putnbr_hex((unsigned int)cmd);
//			ft_putchar(' ');
//			ft_lprintf(1, "%s ", vasm->cmd[(int)str[i]]);
		}
		if (str[i] != 1 && str[i] != 9 && str[i] != 12 && str[i] != 15)
		{
			++i;
			vasm->ocp = str[i];
			++i;
			if ((vasm->ocp & 0xC0) == 64)
			{
				ft_lprintf(vasm->fd, "r%d", str[i]);
			ft_lprintf(1, "%d %d\n", i, str[i]);
//				ft_putnbr_hex((unsigned int)str[i]);
	//		ft_putchar(' ');
//				ft_lprintf(1, "r%d", str[i]);
				++i;
			}
			else if ((vasm->ocp & 0xC0) == 128)
			{
				if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
				{
					vasm->cor[0] = str[i + 3];
					vasm->cor[1] = str[i + 2];
					vasm->cor[2] = str[i + 1];
					vasm->cor[3] = str[i];
					vasm->icor = (int)vasm->cor[3];// + 0x100 * vasm->cor[2] + 0x10000 * vasm->cor[1] + 0x1000000 * vasm->cor[0];
			ft_lprintf(1, "%d %x %x %x %x\n", i, vasm->cor[0], vasm->cor[1], vasm->cor[2], vasm->cor[3]);
			ft_lprintf(1, "%d %d\n", i, vasm->icor);
//					write(1, &vasm->cor, 4);
	//				ft_putnbr_hex((unsigned int)vasm->cor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, ",%c%d", '%', vasm->cor);
//					ft_lprintf(1, ",%c%d", '%', vasm->cor);
					i += 4;
				}
				else
				{
					vasm->scor[0] = str[i + 1];
					vasm->scor[1] = str[i];
			ft_lprintf(1, "%d %x %x\n", i, vasm->scor[0], vasm->scor[1]);
//					write(1, &vasm->scor, 2);
//					ft_putnbr_hex((unsigned int)vasm->scor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, ",%c%d", '%', (short int)vasm->scor);
//					ft_lprintf(1, ",%c%d", '%', (short int)vasm->scor);
					i += 2;
				}
//				ft_lprintf(vasm->fd, "%c%d", '%', ft_atoi(str + i));
//				ft_lprintf(1, "%c%d", '%', ft_atoi(str + i));
//				if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
//					i += 4;
//				else
//					i += 2;
			}
			else if ((vasm->ocp & 0xC0) == 192)
			{
				ft_lprintf(vasm->fd, "%d", ft_atoi(str + i));
				ft_lprintf(1, "%d", ft_atoi(str + i));
				i += 2;
			}
			if ((vasm->ocp & 0x30) == 16)
			{
				ft_lprintf(vasm->fd, ",r%d", str[i]);
				ft_lprintf(1, ",r%d", str[i]);
				++i;
			}
			else if ((vasm->ocp & 0x30) == 32)
			{
				if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
				{
					vasm->cor[0] = str[i + 3];
					vasm->cor[1] = str[i + 2];
					vasm->cor[2] = str[i + 1];
					vasm->cor[3] = str[i];
					vasm->icor = vasm->cor[0] + 256 * vasm->cor[1] + 256 * 256 * vasm->cor[2] + 256 * 256 * 256 * vasm->cor[3];
			ft_lprintf(1, "%d %x %x %x %x\n", i, vasm->cor[0], vasm->cor[1], vasm->cor[2], vasm->cor[3]);
			ft_lprintf(1, "%d %d\n", i, vasm->icor);
//					write(1, &vasm->cor, 4);
	//				ft_putnbr_hex((unsigned int)vasm->cor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, ",%c%d", '%', vasm->icor);
//					ft_lprintf(1, ",%c%d", '%', vasm->cor);
					i += 4;
				}
				else
				{
					vasm->scor[0] = str[i + 1];
					vasm->scor[1] = str[i];
					vasm->icor = vasm->scor[0] + 256 * vasm->scor[1];
			ft_lprintf(1, "%d %x %x\n", i, vasm->scor[0], vasm->scor[1]);
			ft_lprintf(1, "%d %x\n", i, vasm->icor);
//					write(1, &vasm->scor, 2);
//					ft_putnbr_hex((unsigned int)vasm->scor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, ",%c%d", '%', vasm->icor);
//					ft_lprintf(1, ",%c%d", '%', (short int)vasm->scor);
					i += 2;
				}
			}
			else if ((vasm->ocp & 0x30) == 48)
			{
				ft_lprintf(vasm->fd, ",%d", ft_atoi(str + i));
				ft_lprintf(1, ",%d", ft_atoi(str + i));
				i += 2;
			}
			else if ((vasm->ocp & 0x30) >> 3 == 0)
			{
				ft_lprintf(vasm->fd, "\n");
				ft_lprintf(1, "\n");
			}
			if ((vasm->ocp & 0x0c) == 4)
			{
				ft_lprintf(vasm->fd, ",r%d", str[i]);
				ft_lprintf(1, ",r%d", str[i]);
				++i;
			}
			else if ((vasm->ocp & 0x0c) == 8)
			{
				if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
				{
					vasm->cor[0] = str[i + 3];
					vasm->cor[1] = str[i + 2];
					vasm->cor[2] = str[i + 1];
					vasm->cor[3] = str[i];
					vasm->icor = vasm->cor[0] + 256 * vasm->cor[1] + 256 * 256 * vasm->cor[2] + 256 * 256 * 256 * vasm->cor[3];
			ft_lprintf(1, "%d %d\n", i, vasm->cor);
//					write(1, &vasm->cor, 4);
	//				ft_putnbr_hex((unsigned int)vasm->cor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, ",%c%d", '%', vasm->icor);
//					ft_lprintf(1, ",%c%d", '%', vasm->cor);
					i += 4;
				}
				else
				{
					vasm->scor[0] = str[i + 1];
					vasm->scor[1] = str[i];
					vasm->icor = vasm->scor[0] + 256 * vasm->scor[1];
			ft_lprintf(1, "%d %x %x\n", i, vasm->scor[0], vasm->scor[1]);
			ft_lprintf(1, "%d %x\n", i, vasm->icor);
//					write(1, &vasm->scor, 2);
//					ft_putnbr_hex((unsigned int)vasm->scor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, ",%c%d", '%', vasm->icor);
//					ft_lprintf(1, ",%c%d", '%', (short int)vasm->scor);
					i += 2;
				}
	//			ft_lprintf(1, "%d", i);
//					write(1, &vasm->cor, 4);
	//				ft_putnbr_hex((unsigned int)vasm->cor);
//			ft_putchar(' ');
//				ft_lprintf(vasm->fd, ",%c%d", '%', ft_atoi(str + i));
	//			ft_lprintf(1, ",%c%d", '%', ft_atoi(str + i));
//				if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
//					i += 4;
//				else
//					i += 2;
			}
			else if ((vasm->ocp & 0x0c) == 12)
			{
				ft_lprintf(vasm->fd, ",%d", ft_atoi(str + i));
				ft_lprintf(1, ",%d", ft_atoi(str + i));
				i += 2;
			}
			else if ((vasm->ocp & 0x0c) == 0)
			{
				ft_lprintf(vasm->fd, "\n");
				ft_lprintf(1, "\n");
			}
			if ((vasm->ocp & 0x0c) && (vasm->ocp & 0x03) == 0)
			{
				ft_lprintf(vasm->fd, "\n");
				ft_lprintf(1, "\n");
			}
		}
		else
		{
			++i;
			if (cmd == 9 || cmd == 12 || cmd == 15)
			{
				vasm->scor[0] = str[i + 1];
					vasm->scor[1] = str[i];
					vasm->icor = (short int)(vasm->scor[0] + 256 * vasm->scor[1]);
			ft_lprintf(1, "%d %x %x\n", i, vasm->scor[0], vasm->scor[1]);
//					write(1, &vasm->scor, 2);
//					ft_putnbr_hex((unsigned int)vasm->scor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, "%c%d\n", '%', vasm->icor);
//					ft_lprintf(1, ",%c%d", '%', (short int)vasm->scor);
					i += 2;
//				ft_lprintf(vasm->fd, "%c%d\n", '%', ft_atoi(str + i));
//				ft_lprintf(1, "%c%d\n", '%', ft_atoi(str + i));
//				i += 2;
			}
			if (cmd == 1)
			{
				vasm->cor[0] = str[i + 3];
					vasm->cor[1] = str[i + 2];
					vasm->cor[2] = str[i + 1];
					vasm->cor[3] = str[i];
					vasm->icor = vasm->cor[0] + 256 * vasm->cor[1] + 256 * 256 * vasm->cor[2] + 256 * 256 * 256 * vasm->cor[3];
			ft_lprintf(1, "%d %x %x %x %x\n", i, vasm->cor[0], vasm->cor[1], vasm->cor[2], vasm->cor[3]);
			ft_lprintf(1, "%d %d\n", i, vasm->icor);
//					write(1, &vasm->cor, 4);
	//				ft_putnbr_hex((unsigned int)vasm->cor);
//			ft_putchar(' ');
					ft_lprintf(vasm->fd, "%c%d\n", '%', vasm->icor);
//					ft_lprintf(1, ",%c%d", '%', vasm->cor);
					i += 4;
//				ft_lprintf(vasm->fd, ",%c%d\n", '%', ft_atoi(str + i));
//				ft_lprintf(1, "%c%d\n", '%', ft_atoi(str + i));
//				i += 4;
			}
		}
	}
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
