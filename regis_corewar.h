/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regis_corewar.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:59:57 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/15 19:40:09 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					*byte_analysis(void *adr);
int					get_direct_value(unsigned char op, void *adr);
int					get_reg_value(t_proc *processus, void *adr);
int					get_indirect_value(t_proc *processus, t_corewar *corewar,
					void *adr);
int					get_value(t_proc *proc, t_corewar *corewar, int nbr,
					unsigned char op, void *adr);
int					get_indirect_value_nm(t_proc *processus, t_corewar *corewar,
					void *adr);
int					get_value_nm(t_proc *proc, t_corewar *cr, int nbr,
					unsigned char op, void *adr);
void				live(t_proc *proc, t_corewar *corewar);
void				*get_pc(int	index, t_corewar *corewar);
void				c_and(t_proc *proc, t_corewar *corewar, unsigned char op);
void				c_or(t_proc *proc, t_corewar *corewar, unsigned char op);
void				c_xor(t_proc *proc, t_corewar *corewar, unsigned char op);
void				ld(t_proc *proc, t_corewar *corewar, unsigned char op);
void				lld(t_proc *proc, t_corewar *corewar, unsigned char op);
void				ldi(t_proc *proc, t_corewar *corewar, unsigned char op);
void				lldi(t_proc *proc, t_corewar *corewar, unsigned char op);
void				st(t_proc *proc, t_corewar *corewar);
void				sti(t_proc *proc, t_corewar *corewar, unsigned char op);
int					set_index(void *adr);
void				add(t_proc *proc, t_corewar *corewar);
void				sub(t_proc *proc, t_corewar *corewar);
void				zjmp(t_proc *proc, t_corewar *corewar);
void				c_fork(t_proc *proc, t_corewar *corewar);
void				lfork(t_proc *proc, t_corewar *corewar);
void				aff(t_proc *proc, t_corewar *corewar);
int					get_int_indirect_value(void *adr);
void				print_bit(t_corewar *corewar, int pc, int p1);
unsigned int		set_pc(int tmp);
void				change_carry(t_proc *processus, int p1);
int					move_pc(int	tab, unsigned char op);
