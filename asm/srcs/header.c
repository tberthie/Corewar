/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:50:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 15:52:26 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			get_header(t_asm *vasm)
{
	t_inst		*tmp;

	ft_bzero(&(vasm->header), sizeof(t_header));
	vasm->header.magic = ft_revint(COREWAR_EXEC_MAGIC);
	vasm->header.prog_size = ft_revint(vasm->cor_size);
	tmp = vasm->labreg;
	tmp = tmp->next;
	ft_strncpy(vasm->header.prog_name, tmp->content + 1,
			ft_strlen(tmp->content + 2));
	tmp = tmp->next->next;
	ft_strncpy(vasm->header.comment, tmp->content + 1,
			ft_strlen(tmp->content + 2));
}

void			put_header(t_asm *vasm)
{
	get_header(vasm);
	write(vasm->fd, &(vasm->header), sizeof(t_header));
}

t_inst			*store_header(t_asm *vasm, t_inst *tmp, int i)
{
	if (!vasm->labreg->content)
	{
		first_node(vasm, i, get_iword(vasm->s[i]));
		ft_strncpy(vasm->labreg->content, vasm->s[i] + ft_trim(vasm->s[i]),
				get_iword(vasm->s[i] + ft_trim(vasm->s[i])));
		tmp = vasm->labreg;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		tmp = other_node(tmp->next, i, ft_strichr(vasm->s[i], LABEL_CHAR));
		ft_strncpy(tmp->content, vasm->s[i] + ft_trim(vasm->s[i]),
				get_iword(vasm->s[i] + ft_trim(vasm->s[i])));
	}
	return (store_header_data(vasm, tmp, i));
}

t_inst			*store_header_data(t_asm *vasm, t_inst *tmp, int i)
{
	if (!vasm->labreg->content)
	{
		first_node(vasm, i, ft_strichr_last(vasm->s[i], '"') -
				ft_strichr(vasm->s[i], '"') + 1);
		ft_strncpy(vasm->labreg->content, vasm->s[i] + ft_strichr(vasm->s[i],
				'"'), ft_strichr_last(vasm->s[i], '"') -
				ft_strichr(vasm->s[i], '"') + 1);
		tmp = vasm->labreg;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_inst *)malloc(sizeof(t_inst))))
			exit(EXIT_FAILURE);
		tmp = other_node(tmp->next, i, ft_strichr_last(vasm->s[i], '"') -
				ft_strichr(vasm->s[i], '"') + 1);
		ft_strncpy(tmp->content, vasm->s[i] + ft_strichr(vasm->s[i],
				'"'), ft_strichr_last(vasm->s[i], '"') -
				ft_strichr(vasm->s[i], '"') + 1);
	}
	return (tmp);
}
