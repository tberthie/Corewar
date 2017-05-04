/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:25:04 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/04 14:34:49 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"
# include <sys/stat.h>
# include "../../resources/example/op.h"

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
	char		cor[4];
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
	void		(*insttab[17])(struct s_asm *, char *);
	void		(*checktab[17])(struct s_asm *, char *);
	t_inst		*labreg;
	t_inst		*instruct;
}				t_asm;

void			error(t_asm *v_asm);
void			put_asm(t_asm *vasm);
void			get_labels(t_asm *vasm, int i, int lbl, char *inst);
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
int				check_reg(char *inst);
int				check_dir(t_asm *vasm, char *inst);
int				check_ind(char *inst);
void			check_label(t_asm *vasm, int i);
void			check_header(t_asm *vasm, int i);
void			check_asm(t_asm *vasm, int i, char *inst);
int				find_ocp(t_inst *node, int param, int oct, int i);
void			init_checktab(t_asm *vasm);
void			init_cmd(t_asm *vasm);
void			init_asm(t_asm *vasm);
void			free_all(t_asm *vasm);
void			get_header(t_asm *vasm);
void			put_four_zero(t_asm *vasm);
void			put_magic(t_asm *vasm);
void			put_header(t_asm *vasm, int i);
void			offset_pos(t_asm *vasm, t_inst *node, t_inst *off);
void			offset_neg(t_asm *vasm, t_inst *node, t_inst *off);
void			put_offset(t_asm *vasm, t_inst *node);
void			get_cor_size(t_asm *vasm);
void			first_node(t_asm *vasm, int i, int size);
t_inst			*other_node(t_inst *tmp, int i, int size);
void			store_regdirind(t_asm *vasm, t_inst *tmp, int i, char *inst);
void			get_cor_size(t_asm *vasm);
void			put_ind(t_asm *vasm, t_inst *node, int ind);
void			put_dir_neg(t_asm *vasm, t_inst *node, int dir, size_t i);
void			put_dir(t_asm *vasm, t_inst *node, int dir, size_t i);
void			put_reg(t_asm *vasm, t_inst *node);
void			put_cmd(t_asm *vasm, t_inst *node);

#endif
