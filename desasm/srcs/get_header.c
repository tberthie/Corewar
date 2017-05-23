/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:21:32 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:39:59 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	get_magic_number(t_asm *vasm, char *str)
{
	vasm->magic = str[3] & 0x000000ff;
	vasm->magic += (str[2] * 0xff) & 0x0000ff00;
	vasm->magic += (str[1] * 0xffff) & 0x00ff0000;
	vasm->magic += (str[0] * 0xffffff) & 0xff000000;
}

void	get_name(t_asm *vasm, char *str)
{
	int i;

	i = 4;
	if (!(vasm->name = (char *)malloc(ft_strlen(str + i) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->name, str + i, ft_strlen(str + i));
	ft_lprintf(vasm->fd, ".name %c%s%c\n", '"', vasm->name, '"');
}

void	get_prog_size(t_asm *vasm, char *str)
{
	vasm->cor_size = str[PROG_NAME_LENGTH + 11] & 0x000000ff;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 10] * 0xff) & 0x0000ff00;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 9] * 0xffff) & 0x00ff0000;
	vasm->cor_size += (str[PROG_NAME_LENGTH + 8] * 0xffffff) & 0xff000000;
}

void	get_comment(t_asm *vasm, char *str)
{
	int begin;

	begin = 12 + PROG_NAME_LENGTH;
	if (!(vasm->comment = (char *)malloc(ft_strlen(str + begin) + 1)))
		exit(EXIT_FAILURE);
	ft_strncpy(vasm->comment, str + begin, ft_strlen(str + begin));
	ft_lprintf(vasm->fd, ".comment %c%s%c\n", '"', vasm->comment, '"');
}
