/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:44:53 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/15 15:25:00 by gthomas          ###   ########.fr       */
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

void		is_header(t_asm *vasm)
{
	int line;
	int i;
	int name;
	int comment;

	line = vasm->labreg->line;
	i = 0;
	name = 0;
	comment = 0;
	while (i < line)
	{
		if (!ft_strncmp(vasm->s[i], NAME_CMD_STRING,
					ft_strlen(NAME_CMD_STRING)))
			++name;
		if (!ft_strncmp(vasm->s[i], COMMENT_CMD_STRING,
					ft_strlen(COMMENT_CMD_STRING)))
			++comment;
		++i;
	}
	if (name != 1)
		error(vasm, 1);
	if (comment != 1)
		error(vasm, 2);
}

void		check_header(t_asm *vasm, int i)
{
	is_header(vasm);
	if (!ft_strncmp(vasm->s[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		vasm->name_line = i;
		if (ft_strichr_cnt(vasm->s[i], '"') != 2 || ft_strichr_last(vasm->s[i],
					'"') - ft_strichr(vasm->s[i], '"') == 1 ||
				ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i], '"')
				> PROG_NAME_LENGTH || vasm->s[i][ft_strichr_last(vasm->s[i],
					'"') + 1] != '\0')
			error(vasm, 1);
	}
	else if (!ft_strncmp(vasm->s[i], COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
	{
		vasm->comment_line = i;
		if (ft_strichr_cnt(vasm->s[i], '"') != 2 || ft_strichr_last(vasm->s[i],
					'"') - ft_strichr(vasm->s[i], '"') == 1 ||
				ft_strichr_last(vasm->s[i], '"') - ft_strichr(vasm->s[i], '"')
				> COMMENT_LENGTH || vasm->s[i][ft_strichr_last(vasm->s[i],
					'"') + 1] != '\0')
			error(vasm, 2);
	}
}

void		check_order(t_asm *vasm)
{
	if (vasm->name_line >= 0 && vasm->comment_line >= 0 &&
			vasm->inst_line >= 0)
	{
		if (vasm->name_line >= vasm->comment_line || vasm->inst_line <=
				vasm->name_line || vasm->inst_line <= vasm->comment_line)
			error(vasm, 6);
	}
	else if (vasm->inst_line >= 0 && (vasm->name_line == -1 ||
				vasm->comment_line == -1))
		error(vasm, 6);
}

void		check_asm(t_asm *vasm, int i, char *inst)
{
	while (i < vasm->file_lines)
	{
		check_order(vasm);
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
		else if (vasm->s[i][0] != COMMENT_CHAR)
			check_header(vasm, i);
		++i;
	}
}
