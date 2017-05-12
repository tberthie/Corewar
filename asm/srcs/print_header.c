/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:50:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 12:12:37 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_header(t_asm *vasm, int i, int nb)
{
	while (i < vasm->file_lines)
	{
		if (!ft_strncmp(vasm->s[i], NAME_CMD_STRING,
					ft_strlen(NAME_CMD_STRING)))
		{
			++nb;
			ft_lprintf(1, "Name : %s\n", vasm->s[i] + ft_strichr(vasm->s[i],
						'"'));
		}
		if (!ft_strncmp(vasm->s[i], COMMENT_CMD_STRING,
					ft_strlen(COMMENT_CMD_STRING)))
		{
			++nb;
			ft_lprintf(1, "Comment : %s\n", vasm->s[i] + ft_strichr(vasm->s[i],
						'"'));
		}
		if (nb == 2)
		{
			ft_lprintf(1, "\n");
			break ;
		}
		++i;
	}
}
