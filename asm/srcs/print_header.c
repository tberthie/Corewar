/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:50:41 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 11:27:29 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		print_header(t_asm *vasm)
{
	ft_lprintf(1, "Name : %c%s%c\n", '"', vasm->header.prog_name, '"');
	ft_lprintf(1, "Comment : %c%s%c\n", '"', vasm->header.comment, '"');
	ft_lprintf(1, "\n");
}
