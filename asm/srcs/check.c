/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:44:53 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/08 16:49:59 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		check_label(t_asm *vasm, int i)
{
	int		j;
	int		size;

	j = 0;
	size = ft_strichr(vasm->s[i], LABEL_CHAR);
	if (!size || size > T_LAB + 1)
		error(vasm, 3);
	while (j < size)
	{
		if (ft_strichr(LABEL_CHARS, vasm->s[i][j]) == -1)
			error(vasm, 3);
		++j;
	}
}

void		check_header(t_asm *vasm, int i)
{
//	ft_lprintf(1, "Je rentre ici\n");
	if (!ft_strncmp(vasm->s[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (ft_strichr_cnt(vasm->s[i], '"') != 2)
			error(vasm, 3);
		if (ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i], '"') == 1
				|| ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i],
					'"') > PROG_NAME_LENGTH)
			error(vasm, 3);
		if (vasm->s[i][ft_strichr_last(vasm->s[i], '"') + 1] != '\0')
			error(vasm, 3);
	}
	else if (!ft_strncmp(vasm->s[i], COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
	{
		if (ft_strichr_cnt(vasm->s[i], '"') != 2)
			error(vasm, 3);
		if (ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i], '"') == 1
				|| ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i],
					'"') > COMMENT_LENGTH)
			error(vasm, 3);
		if (vasm->s[i][ft_strichr_last(vasm->s[i], '"') + 1] != '\0')
			error(vasm, 3);
	}
	else
		error(vasm, 3);
}

void		check_asm(t_asm *vasm, int i, char *inst)
{
	while (i < vasm->file_lines)
	{
//		ft_lprintf(1, "%s\n", vasm->s[i]);
		if (ft_stristr(vasm->s[i], NAME_CMD_STRING) == -1 &&
				ft_stristr(vasm->s[i], COMMENT_CMD_STRING) == -1 &&
				vasm->s[i][0] != COMMENT_CHAR)
		{
			vasm->inst_line = i;
			inst = vasm->s[i];
			if (ft_strichr(vasm->s[i], LABEL_CHAR) != -1 &&
					vasm->s[i][ft_strichr(vasm->s[i], LABEL_CHAR) + 1] == ' ')
			{
				check_label(vasm, i);
				inst = vasm->s[i] + ft_strichr(vasm->s[i], LABEL_CHAR) + 1;
				inst += ft_trim(inst);
			}
			vasm->command = ft_stritabstr(vasm->cmd, inst,
			ft_strichr(inst, ' '));
			vasm->checktab[vasm->command](vasm, inst +
			ft_strichr(inst, ' ') + 1);
		}
		else if (vasm->s[i][0] != COMMENT_CHAR && (!ft_stristr(vasm->s[i],
			NAME_CMD_STRING) || !ft_stristr(vasm->s[i], COMMENT_CMD_STRING)))
			check_header(vasm, i);
		++i;
	}
}
