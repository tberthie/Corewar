/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 23:42:54 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/03 15:38:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static char		*get_hex(unsigned char hex)
{
	char			*str;

	str = ft_m(3);
	str[0] = ("0123456789ABCDEF")[hex / 16 % 16];
	str[1] = ("0123456789ABCDEF")[hex % 16];
	str[2] = 0;
	return (str);
}

static void		render_op(t_corewar *corewar, t_visual *visu, int x, int y)
{
	SDL_Rect		rc;
	unsigned char	hex;
	int				index;
	char			*tmp;

	index = x + y * MEM_SIZE / 64;
	hex = *(unsigned char*)(corewar->memory + index);
	if (hex || visu->color[index] != 0x50505050)
	{
		rc = rec(((double)x / 64) * 1152.0 + 20, ((double)y / (MEM_SIZE / 64)) *
		960.0 + 20, (1.0 / 64.0 * 1152.0), (1.0 / (MEM_SIZE / 64)) * 960.0);
		SDL_FillRect(visu->sf, &rc, visu->color[index]);
		rc.x += 2;
		rc.y += 2;
		dhex(visu, (tmp = get_hex(hex)), visu->color[index], rc);
		ft_free(tmp);
	}
}

void			render_hex(t_corewar *corewar, t_visual *visu)
{
	int				y;
	int				x;

	y = 0;
	while (y < MEM_SIZE / 64)
	{
		x = 0;
		while (x < 64)
		{
			render_op(corewar, visu, x, y);
			x++;
		}
		y++;
	}
}
