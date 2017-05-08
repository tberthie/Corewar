/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:50:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:50:30 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		get_header(t_asm *vasm)
{
	int		tmp;

	tmp = ft_stritabstr(vasm->s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	if (tmp == -1)
		error(vasm, 1);
	if (!(vasm->name = (char *)malloc(PROG_NAME_LENGTH + 1)))
		exit(EXIT_FAILURE);
	ft_bzero(vasm->name, PROG_NAME_LENGTH + 1);
	ft_strncpy(vasm->name, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1,
			ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"')
			- 1);
	tmp = ft_stritabstr(vasm->s, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING));
	if (tmp == -1)
		error(vasm, 2);
	if (!(vasm->comment = (char *)malloc(COMMENT_LENGTH + 1)))
		exit(EXIT_FAILURE);
	ft_bzero(vasm->comment, COMMENT_LENGTH + 1);
	ft_strncpy(vasm->comment, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1,
			ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"')
			- 1);
}

void		put_four_zero(t_asm *vasm)
{
	write(vasm->fd, &vasm->zero, 1);
	write(vasm->fd, &vasm->zero, 1);
	write(vasm->fd, &vasm->zero, 1);
	write(vasm->fd, &vasm->zero, 1);
}

void		put_magic(t_asm *vasm)
{
	int		i;
	char	magic_nb[4];

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

void		put_header(t_asm *vasm, int i)
{
	vasm->cor[0] = 0;
	vasm->cor[1] = 0;
	vasm->cor[2] = 0;
	if (vasm->cor_size > 65535)
		vasm->cor[1] = (vasm->cor_size & 0x00ff0000) >> 16;
	else if (vasm->cor_size > 255)
		vasm->cor[2] = (vasm->cor_size & 0x0000ff00) >> 8;
	vasm->cor[3] = (vasm->cor_size & 0x000000ff);
	put_magic(vasm);
	while (i < PROG_NAME_LENGTH)
	{
		write(vasm->fd, &vasm->name[i], 1);
		++i;
	}
	i = 0;
	put_four_zero(vasm);
	write(vasm->fd, &vasm->cor, 4);
	while (i < COMMENT_LENGTH)
	{
		write(vasm->fd, &vasm->comment[i], 1);
		++i;
	}
	put_four_zero(vasm);
}
