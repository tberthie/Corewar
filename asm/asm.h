/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:25:04 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/01 17:15:13 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "./libft/includes/libft.h"
#include "./libft/includes/get_next_line.h"
# include <sys/stat.h>
# include "../resources/example/op.h"

typedef struct	s_inst
{
	char		*content;
	size_t		content_size;
	size_t		line;
	struct s_inst	*next;
}				t_inst;

typedef struct	s_asm
{
	char		**cmd;
	char		**s;
	char		*name;
	char		*comment;
	int			label;
	int			zero;
	int			ff;
	int			ret;
	char		*file_name;
	char		*tmp;
	char		*file;
	int			fd;
	int			inst;
	int			command;
	int			file_lines;
	int			inst_line;
	int			cor_size;
//	char		cor_size[4];
	void		(*insttab[17])(struct s_asm *, char *);
	void		(*checktab[17])(struct s_asm *, char *);
	t_inst		*labreg;
	t_inst		*instruct;
}				t_asm;

void			error(t_asm *v_asm);
void			put_asm(t_asm *vasm);
void			get_labels(t_asm *vasm);
int				ft_lstntabstr(t_inst **begin, char *str, int size, int nb);
void			check_none(t_asm *vasm, char *inst);
void			check_live(t_asm *vasm, char *inst);
void			check_ld(t_asm *vasm, char *inst);
void			check_st(t_asm *vasm, char *inst);
void			check_add(t_asm *vasm, char *inst);
void			check_sub(t_asm *vasm, char *inst);
void			check_and(t_asm *vasm, char *inst);
void			check_or(t_asm *vasm, char *inst);
void			check_xor(t_asm *vasm, char *inst);
void			check_zjmp(t_asm *vasm, char *inst);
void			check_ldi(t_asm *vasm, char *inst);
void			check_sti(t_asm *vasm, char *inst);
void			check_fork(t_asm *vasm, char *inst);
void			check_lld(t_asm *vasm, char *inst);
void			check_lldi(t_asm *vasm, char *inst);
void			check_lfork(t_asm *vasm, char *inst);
void			check_aff(t_asm *vasm, char *inst);
int				find_ocp(t_inst *node);
void			init_checktab(t_asm *vasm);
void			init_cmd(t_asm *vasm);
void			free_all(t_asm *vasm);

#endif
