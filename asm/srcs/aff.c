/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 14:52:47 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/12 12:12:38 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_hex(t_asm *vasm, char *str)
{
	vasm->s = ft_strsplit(str, '\n');
	vasm->file_lines = ft_ptrlen(vasm->s);
	get_labels(vasm, -1, 0, NULL);
	init_checktab(vasm);
	check_asm(vasm, 0, NULL);
	get_cor_size(vasm);
	get_header(vasm);
	ft_lprintf(1, "Dumping annotated program on standard output\n");
	ft_lprintf(1, "Program size : %d bytes\n", vasm->cor_size);
	print_header(vasm, 0, 0);
	print_asm(vasm);
	free_all(vasm);
}

void		aff_parse(t_asm *vasm, char *str)
{
	char	*tmp;

	init_asm(vasm);
	if (!(tmp = ft_parse(str)))
		exit(EXIT_FAILURE);
	init_cmd(vasm);
	print_hex(vasm, tmp);
	if (tmp)
		free(tmp);
}
