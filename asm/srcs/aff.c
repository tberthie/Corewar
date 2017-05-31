/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 14:52:47 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/31 13:49:51 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_hex(t_asm *vasm, char *str)
{
	if (!(vasm->s = ft_splitline(str)))
		error(vasm, 7);
	vasm->file_lines = ft_ptrlen(vasm->s);
	get_labels(vasm, 0, 0);
	init_checktab(vasm);
	check_asm(vasm, vasm->labreg, vasm->labreg);
	get_cor_size(vasm);
	get_header(vasm);
	ft_lprintf(1, "Dumping annotated program on standard output\n");
	ft_lprintf(1, "Program size : %d bytes\n", vasm->cor_size);
	print_header(vasm);
	vasm->inst_line = 0;
	print_asm(vasm);
}

void		aff_parse(t_asm *vasm, char *str)
{
	char	*tmp;

	init_asm(vasm);
	if (!(tmp = ft_parse(str)))
		error(vasm, 5);
	init_cmd(vasm);
	print_hex(vasm, tmp);
	if (tmp)
		free(tmp);
}
