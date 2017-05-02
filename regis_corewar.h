/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regis_corewar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:59:57 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/02 19:52:40 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			*byte_analysis(t_proc *processus, t_corewar *corewar);
int			get_direct_value(t_proc *processus, t_corewar *corewar, unsigned char op);
int			get_indirect_value(t_proc *processus, t_corewar *corewar);
int			get_reg_value(t_proc *processus, t_corewar *corewar);
int			get_value(t_proc *processus, t_corewar *corewar, int nbr, unsigned char op);
int			get_indirect_value_nm(t_proc *processus, t_corewar *corewar);
int			get_value_nm(t_proc *proc, t_corewar *cr, int nbr, unsigned char op);
void		live(t_proc *processus, t_corewar *corewar);
void		*get_pc(t_proc *processus, t_corewar *corewar);
void		c_and(t_proc *processus, t_corewar *corewar, unsigned char op);
void		c_or(t_proc *processus, t_corewar *corewar, unsigned char op);
void		c_xor(t_proc *processus, t_corewar *corewar, unsigned char op);
void		ld(t_proc *processus, t_corewar *corewar, unsigned char op);
void		lld(t_proc *processus, t_corewar *corewar, unsigned char op);
void		ldi(t_proc *processus, t_corewar *corewar, unsigned char op);
void		lldi(t_proc *processus, t_corewar *corewar, unsigned char op);
void		st(t_proc *processus, t_corewar *corewar);
void		sti(t_proc *processus, t_corewar *corewar, unsigned char op);
int			set_index(t_proc *processus, t_corewar *corewar);
void		add(t_proc *processus, t_corewar *corewar);
void		sub(t_proc *processus, t_corewar *corewar);
void		zjmp(t_proc *processus, t_corewar *corewar, unsigned char op);
void		c_fork(t_proc *processus, t_corewar *corewar);
void		lfork(t_proc *processus, t_corewar *corewar);
void		aff(t_proc *processus, t_corewar *corewar);
