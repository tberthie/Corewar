/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:35:05 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 12:59:06 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_dir(t_asm *vasm, int *i, int cmd, char *str)
{
	if (cmd == 1 || cmd == 2 || (cmd >= 6 && cmd <= 8) || cmd == 13)
	{
		vasm->cor[0] = str[*i + 3];
		vasm->cor[1] = str[*i + 2];
		vasm->cor[2] = str[*i + 1];
		vasm->cor[3] = str[*i];
		vasm->icor = vasm->cor[0] + 256 * vasm->cor[1] + 256 * 256 *
			vasm->cor[2] + 256 * 256 * 256 * vasm->cor[3];
		ft_lprintf(vasm->fd, "%c%d", '%', vasm->icor);
		*i += 4;
	}
	else
	{
		vasm->scor[0] = str[*i + 1];
		vasm->scor[1] = str[*i];
		vasm->sicor = vasm->scor[0] + 256 * vasm->scor[1];
		ft_lprintf(vasm->fd, "%c%d", '%', vasm->sicor);
		*i += 2;
	}
}

void	print_ind(t_asm *vasm, int *i, char *str)
{
	vasm->scor[0] = str[*i + 1];
	vasm->scor[1] = str[*i];
	vasm->icor = vasm->scor[0] + 256 * vasm->scor[1];
	ft_lprintf(vasm->fd, "%d", vasm->icor);
	*i += 2;
}

void	print_ocp_1(t_asm *vasm, char *str, int *i, int cmd)
{
	if ((vasm->ocp & 0xC0) == 64)
	{
		ft_lprintf(vasm->fd, "r%d", str[*i]);
		*i += 1;
	}
	else if ((vasm->ocp & 0xC0) == 128)
		print_dir(vasm, i, cmd, str);
	else if ((vasm->ocp & 0xC0) == 192)
		print_ind(vasm, i, str);
	if ((vasm->ocp & 0x30) == 16)
	{
		ft_lprintf(vasm->fd, ",r%d", str[*i]);
		*i += 1;
	}
	else if ((vasm->ocp & 0x30) == 32)
	{
		ft_lprintf(vasm->fd, ",");
		print_dir(vasm, i, cmd, str);
	}
	else if ((vasm->ocp & 0x30) == 48)
	{
		ft_lprintf(vasm->fd, ",");
		print_ind(vasm, i, str);
	}
}

void	print_ocp(t_asm *vasm, char *str, int *i, int cmd)
{
	*i += 1;
	vasm->ocp = str[*i];
	*i += 1;
	print_ocp_1(vasm, str, i, cmd);
	if ((vasm->ocp & 0x0c) == 4)
	{
		ft_lprintf(vasm->fd, ",r%d", str[*i]);
		*i += 1;
	}
	else if ((vasm->ocp & 0x0c) == 8)
	{
		ft_lprintf(vasm->fd, ",");
		print_dir(vasm, i, cmd, str);
	}
	else if ((vasm->ocp & 0x0c) == 12)
	{
		ft_lprintf(vasm->fd, ",");
		print_ind(vasm, i, str);
	}
	if (!((vasm->ocp & 0x30) >> 3) || !(vasm->ocp & 0x0c) ||
			!(vasm->ocp & 0x03))
		ft_lprintf(vasm->fd, "\n");
}
