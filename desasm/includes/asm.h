/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:25:04 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/23 15:58:27 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <sys/stat.h>
# include "../../includes/config.h"

typedef struct	s_asm
{
	char			**cmd;
	char			*name;
	char			*comment;
	unsigned char	cor[4];
	unsigned char	scor[2];
	char			ocp;
	int				icor;
	short int		sicor;
	int				magic;
	char			*file_name;
	int				fd;
	int				cor_size;
}				t_asm;

void			error(t_asm *vasm);
void			put_asm(t_asm *vasm);
void			get_magic_number(t_asm *vasm, char *str);
void			get_name(t_asm *vasm, char *str);
void			get_prog_size(t_asm *vasm, char *str);
void			get_comment(t_asm *vasm, char *str);
void			print_hex(t_asm *vasm, char *str, int nb);
void			print_dir(t_asm *vasm, int *i, int cmd, char *str);
void			print_ind(t_asm *vasm, int *i, char *str);
void			print_ocp_1(t_asm *vasm, char *str, int *i, int cmd);
void			print_ocp(t_asm *vasm, char *str, int *i, int cmd);
void			free_all(t_asm *vasm);
void			init_asm(t_asm *vasm);
void			init_cmd(t_asm *vasm);

#endif
