/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 00:39:10 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 00:39:51 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			render_stats(t_corewar *corewar, t_visual *visu)
{
	text(visu, "fluttershy", 0xff0000, rec(1300, 145, 0, 0));
	dhex(visu, "oh, my, what a scary project", 0, rec(1200, 165, 0, 0));

	text(visu, "1 - fluttershy", 0xa0a0a0, rec(1200, 200, 0, 0));
	text(visu, "DEAD", 0xff0000, rec(1415, 200, 0, 0));

	text(visu, "2 - helltrain", 0x00ff00, rec(1200, 400, 0, 0));

	text(visu, "3 - zork", 0xa0a0a0, rec(1200, 600, 0, 0));

	text(visu, "DEAD", 0xff0000, rec(1415, 600, 0, 0));
	text(visu, "4 - rainbowdash", 0xff00ff, rec(1200, 800, 0, 0));
}
