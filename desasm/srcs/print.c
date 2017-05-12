/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:24:52 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 13:01:23 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		header(t_asm *vasm, char *str)
{
	int i;

	i = 0;
	if ((vasm->fd = open(vasm->file_name, O_RDWR | O_CREAT, 0666)) == -1)
	{
		ft_lprintf(2, "Error in openning / creating %s file", vasm->file_name);
		exit(EXIT_FAILURE);
	}
	get_magic_number(vasm, str);
	get_name(vasm, str);
	get_prog_size(vasm, str);
	get_comment(vasm, str);
	i = 12 + PROG_NAME_LENGTH;
	while (str[i])
		++i;
	while (!str[i])
		++i;
	return (i);
}

void	print_unique(t_asm *vasm, char *str, int *i, int cmd)
{
	*i += 1;
	if (cmd == 9 || cmd == 12 || cmd == 15)
	{
		vasm->scor[0] = str[*i + 1];
		vasm->scor[1] = str[*i];
		vasm->sicor = vasm->scor[0] + 256 * vasm->scor[1];
		ft_lprintf(vasm->fd, "%c%d\n", '%', vasm->sicor);
		*i += 2;
	}
	if (cmd == 1)
	{
		vasm->cor[0] = str[*i + 3];
		vasm->cor[1] = str[*i + 2];
		vasm->cor[2] = str[*i + 1];
		vasm->cor[3] = str[*i];
		vasm->icor = vasm->cor[0] + 256 * vasm->cor[1] + 256 * 256 *
			vasm->cor[2] + 256 * 256 * 256 * vasm->cor[3];
		ft_lprintf(vasm->fd, "%c%d\n", '%', vasm->icor);
		*i += 4;
	}
}

void	print_hex(t_asm *vasm, char *str, int nb)
{
	int i;
	int cmd;

	i = header(vasm, str);
	while (i < nb)
	{
		vasm->ocp = 0;
		if (str[i] > 0 && str[i] < 17)
		{
			cmd = (int)str[i];
			ft_lprintf(vasm->fd, "%s ", vasm->cmd[cmd]);
		}
		else
			error(vasm);
		if (str[i] != 1 && str[i] != 9 && str[i] != 12 && str[i] != 15)
			print_ocp(vasm, str, &i, cmd);
		else
			print_unique(vasm, str, &i, cmd);
	}
	close(vasm->fd);
	free_all(vasm);
}
