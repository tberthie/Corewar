/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:25:04 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/19 11:44:49 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <sys/stat.h>
# include "../../includes/config.h"

typedef struct	s_inst
{
	char			*content;
	size_t			content_size;
	size_t			line;
	struct s_inst	*next;
}				t_inst;

typedef struct	s_asm
{
	char			**cmd;
	char			*str;
	char			**s;
	char			*name;
	char			*comment;
	char			cor[4];
	int				icmd[17];
	unsigned char	acor;
	short int		sicor;
	int				icor;
	int				label;
	int				zero;
	int				ff;
	int				ret;
	int				n;
	int				c;
	char			*file_name;
	char			*tmp;
	char			*file;
	int				fd;
	int				bytes;
	int				size;
	int				inst;
	int				command;
	int				len;
	int				file_lines;
	int				first_line;
	int				inst_line;
	t_inst			*(*checktab[17])(struct s_asm *, t_inst *);
	int				cor_size;
	t_inst			*labreg;
	t_inst			*instruct;
	t_header		header;
}				t_asm;

void			error(t_asm *v_asm, int err);
void			put_asm(t_asm *vasm, t_inst *tmp);
void			get_labels(t_asm *vasm, int i, int lbl);
int				ft_lstntabstr(t_inst **begin, char *str, int size, int nb);
t_inst			*check_none(t_asm *vasm, t_inst *tmp);
t_inst			*check_live(t_asm *vasm, t_inst *tmp);
t_inst			*check_ld(t_asm *vasm, t_inst *tmp);
t_inst			*check_st(t_asm *vasm, t_inst *tmp);
t_inst			*check_add(t_asm *vasm, t_inst *tmp);
t_inst			*check_sub(t_asm *vasm, t_inst *tmp);
t_inst			*check_and(t_asm *vasm, t_inst *tmp);
t_inst			*check_or(t_asm *vasm, t_inst *tmp);
t_inst			*check_xor(t_asm *vasm, t_inst *tmp);
t_inst			*check_zjmp(t_asm *vasm, t_inst *tmp);
t_inst			*check_ldi(t_asm *vasm, t_inst *tmp);
t_inst			*check_sti(t_asm *vasm, t_inst *tmp);
t_inst			*check_fork(t_asm *vasm, t_inst *tmp);
t_inst			*check_lld(t_asm *vasm, t_inst *tmp);
t_inst			*check_lldi(t_asm *vasm, t_inst *tmp);
t_inst			*check_lfork(t_asm *vasm, t_inst *tmp);
t_inst			*check_aff(t_asm *vasm, t_inst *tmp);
int				check_reg(char *inst);
int				check_dir(t_asm *vasm, char *inst);
int				check_ind(t_asm *vasm, char *inst);
void			check_label(t_asm *vasm, t_inst *tmp);
t_inst			*check_header(t_asm *vasm, int name, int comment);
void			check_asm(t_asm *vasm, t_inst *tmp, t_inst *tmp2);
int				find_ocp(t_inst *node, int param, int oct, int i);
void			init_checktab(t_asm *vasm);
void			init_cmd(t_asm *vasm);
void			init_asm(t_asm *vasm);
void			free_all(t_asm *vasm);
void			get_header(t_asm *vasm);
void			put_four_zero(t_asm *vasm);
void			put_magic(t_asm *vasm);
void			put_header(t_asm *vasm);
void			offset_pos(t_asm *vasm, t_inst *node, t_inst *off);
void			offset_neg(t_asm *vasm, t_inst *node, t_inst *off);
void			put_offset_dir(t_asm *vasm, t_inst *node);
void			put_offset_ind(t_asm *vasm, t_inst *node);
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
void			aff_parse(t_asm *vasm, char *str);
void			print_header(t_asm *vasm);
void			print_ind(t_asm *vasm, t_inst *node, int ind);
void			print_ind_int(t_asm *vasm, t_inst *node, int ind);
void			print_dir_neg(t_asm *vasm, t_inst *node, int dir, size_t i);
void			print_dir(t_asm *vasm, t_inst *node, int dir, size_t i);
void			print_dir_int(t_asm *vasm, t_inst *node, int dir);
void			print_reg(t_inst *node);
void			print_cmd(t_asm *vasm, t_inst *node);
void			print_offset(t_asm *vasm, t_inst *node);
void			print_offset_int(t_asm *vasm, t_inst *node);
void			print_off_pos(t_asm *vasm, t_inst *node, t_inst *off);
void			print_off_neg(t_asm *vasm, t_inst *node, t_inst *off);
void			print_asm(t_asm *vasm);
void			print_four_bytes(t_asm *vasm, int offset);
void			print_two_bytes(t_asm *vasm, int offset);
void			four_bytes(t_asm *vasm, int offset);
void			two_bytes(t_asm *vasm, int offset);
void			print_size(t_asm *vasm, t_inst *tmp2, t_inst *tmp, int label);
t_inst			*store_header(t_asm *vasm, t_inst *tmp, int i);
t_inst			*store_header_data(t_asm *vasm, t_inst *tmp, int i);
t_inst			*store_str(t_asm *vasm, t_inst *tmp, int i);
void			get_str(t_asm *vasm, int i);
t_inst			*get_first_inst(t_inst *tmp);
int				get_param(t_inst *tmp);
t_inst			*first_inst(t_asm *vasm);
t_inst			*check_name(t_asm *vasm, t_inst *tmp);
t_inst			*check_comment(t_asm *vasm, t_inst *tmp);
void			cor_usage(t_asm *vasm, char *av);

#endif
