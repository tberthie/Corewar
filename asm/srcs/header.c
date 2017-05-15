/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:50:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:47:51 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			get_header(t_asm *vasm)
{
	int			tmp;

	tmp = ft_stritabstr(vasm->s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	if (!(vasm->name = (char *)malloc(PROG_NAME_LENGTH + 1)))
		exit(EXIT_FAILURE);
	ft_bzero(vasm->name, PROG_NAME_LENGTH + 1);
	ft_strncpy(vasm->name, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1,
			ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"')
			- 1);
	tmp = ft_stritabstr(vasm->s, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING));
	if (!(vasm->comment = (char *)malloc(COMMENT_LENGTH + 1)))
		exit(EXIT_FAILURE);
	ft_bzero(vasm->comment, COMMENT_LENGTH + 1);
	ft_strncpy(vasm->comment, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1,
			ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"')
			- 1);
}

void			put_header(t_asm *vasm)
{
	t_header	header;
	int			tmp;

	ft_bzero(&header, sizeof(t_header));
	header.magic = ft_revint(COREWAR_EXEC_MAGIC);
	header.prog_size = ft_revint(vasm->cor_size);
	tmp = ft_stritabstr(vasm->s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	ft_strncpy(header.prog_name, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"')
			+ 1, ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp],
				'"') - 1);
	tmp = ft_stritabstr(vasm->s, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING));
	ft_strncpy(header.comment, vasm->s[tmp] + ft_strichr(vasm->s[tmp], '"') + 1,
			ft_strichr_last(vasm->s[tmp], '"') - ft_strichr(vasm->s[tmp], '"')
			- 1);
	write(vasm->fd, &header, sizeof(t_header));
}
