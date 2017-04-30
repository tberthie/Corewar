/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:00:50 by ramichia          #+#    #+#             */
/*   Updated: 2017/04/30 16:49:23 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void		modify_carry(t_proc *processus)
{
	if (processus->carry == 1)
		processus->carry = 0;
	else
		processus->carry = 1;
}

void 	live(t_proc *processus, t_corewar *corewar)
{
	t_champ	*lat_champ;

	processus->live++;
	last_champ = get_player(corewar, processus);
	corewar->last_alive = last_champ->number;
	processus->pc+= 5;
}
void 	*get_pc(t_proc *processus, t_corewar *corewar)
{
	void 	*adr;

	if (MEM_SIZE < processus->pc)
		processus->pc = 0;
	adr = corewar->memory + processus->pc;
	return(adr);
}

void 	c_and(t_proc *processus, t_corewar *corewar)
{
	char			*p1;
	char			*p2;
	int				*tab;
	unsigned int 	*tmp;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	processus->pc++;
	p1 = get_value(processus, corewar, REG_SIZE, tab[0]);
	p2 = get_value(processus, corewar,REG_SIZE, tab[1]);
	tmp = (unsigned int*)get_adr_reg(processus, corewar);
	*tmp = (unsigned int)p1 & (unsigned int)p2;
	modify_carry(processus);
	processus->pc++;
}

void 	c_or(t_proc *processus, t_corewar *corewar)
{
	char			*p1;
	char			*p2;
	int				*tab;
	unsigned int 	*tmp;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	processus->pc++;
	p1 = get_value(processus, corewar, REG_SIZE, tab[0]);
	p2 = get_value(processus, corewar,REG_SIZE, tab[1]);
	tmp = (unsigned int*)get_adr_reg(processus, corewar);
	*tmp = (unsigned int)p1 | (unsigned int)p2;
	modify_carry(processus);
	processus->pc++;
}

void 	c_xor(t_proc *processus, t_corewar *corewar)
{
	char			*p1;
	char			*p2;
	int				*tab;
	unsigned int 	*tmp;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	processus->pc++;
	p1 = get_value(processus, corewar, REG_SIZE, tab[0]);
	p2 = get_value(processus, corewar,REG_SIZE, tab[1]);
	tmp = (unsigned int*)get_adr_reg(processus, corewar);
	*tmp = (unsigned int)p1 ^ (unsigned int)p2;
	modify_carry(processus);
	processus->pc++;
}

void 	ld(t_proc *processus, t_corewar *corewar)
{
	char	*p1;
	int 	*tmp;
	int		*tab;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	p1 = get_value(processus, corewar, REG_SIZE, tab[0]);
	tmp = (int*)get_adr_reg(processus, corewar);
	*tmp = (int)p1;
	modify_carry(processus);
	processus->pc++;
}

void 	lld(t_proc *processus, t_corewar *corewar)
{
	char	*p1;
	int 	*tmp;
	int		*tab;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	p1 = get_value_nm(processus, corewar, REG_SIZE, tab[0]);
	tmp = (int*)get_adr_reg(processus, corewar);
	*tmp = (int)p1;
	modify_carry(processus);
	processus->pc++;
}

void 	ldi(t_proc *processus, t_corewar *corewar)
{
	int		*tab;
	void 	*tmp;
	char	*p1;
	unsigned int nbr;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	p1 = get_value(processus, corewar, IND_SIZE, tab[0]);
	nbr = (int)p1 + (int)get_value(processus, corewar, REG_SIZE, tab[1]);
	tmp = get_adr_reg(processus, corewar);
	ft_memcpy(tmp, get_pc(processus, corewar) + (nbr % IDX_MOD), REG_SIZE);
	modify_carry(processus);
	processus->pc ++;
}

void 	lldi(t_proc *processus, t_corewar *corewar)
{
	int		*tab;
	void 	*tmp;
	char	*p1;
	unsigned int nbr;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	p1 = get_value_nm(processus, corewar, IND_SIZE, tab[0]);
	nbr = (int)p1 + (int)get_value_nm(processus, corewar, REG_SIZE, tab[1]);
	tmp = get_adr_reg(processus, corewar);
	ft_memcpy(tmp, get_pc(processus, corewar) + nbr , REG_SIZE);
	modify_carry(processus);
	processus->pc ++;
}

void 	st(t_proc *processus, t_corewar *corewar)
{
	char	*p1;
	char	*p2;
	int		*tab;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	p1 = get_reg_value(processus, corewar);
	p2 = get_adr_modulo(processus, corewar, tab[1]);
	p2 = p1;
}

void 	sti(t_proc *processus, t_corewar *corewar)
{
	int				*tab;
	unsigned int 	*tmp;
	char			*p1;
	char 			*p2;
	char 			*p3;

	processus->pc++;
	tab = byte_analysis(processus, corewar);
	p1 = get_reg_value(processus, corewar);
	p2 = get_value(processus, corewar, REG_SIZE, tab[1]);
	p3 = get_value(processus, corewar, REG_SIZE, tab[2]);
	if ((unsigned int)p2 + (unsigned int)p3 < MEM_SIZE)
		tmp = (unsigned int*)(corewar->memory + (unsigned int)p2 + (unsigned int)p3);
	else
		tmp = (unsigned int*)corewar->memory;
	*tmp = (unsigned int)p1;
	processus->pc++;
}

void 	add(t_proc *processus, t_corewar *corewar)
{
	int		*p3;
	char 	*p1;
	char 	*p2;

	processus->pc+= 2;
	p1 = get_reg_value(processus, corewar);
	p2 = get_reg_value(processus, corewar);
	p3 = (int*)get_adr_reg(processus, corewar);
	*p3 = (unsigned int)p1 + (unsigned int)p2;
	modify_carry(processus);
}

void 	sub(t_proc *processus, t_corewar *corewar)
{
	int		*p3;
	char 	*p1;
	char 	*p2;

	processus->pc+= 2;
	p1 = get_reg_value(processus, corewar);
	p2 = get_reg_value(processus, corewar);
	p3 = (int*)get_adr_reg(processus, corewar);
	*p3 = (unsigned int)p1 - (unsigned int)p2;
	modify_carry(processus);
}

void 	zjmp(t_proc *processus, t_corewar *corewar)
{
	void 	*tmp;
	int 	p1;

	processus->pc++;
	tmp = get_pc(processus, corewar);
	p1 = (int)tmp;
	if (processus->carry == 1)
		processus->pc = processus->pc + (p1 % IDX_MOD);
	if ((int)processus->pc < 0 || MEM_SIZE < processus->pc)
		processus->pc = 0;
}

void 	c_fork(t_proc *processus, t_corewar *corewar)
{
	void 			*tmp;
	unsigned int	p1;
	t_proc			*processus2;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc++;
	tmp = get_pc(processus, corewar);
	p1 = (unsigned int)tmp;
	processus2->pc = processus->pc + (p1 % IDX_MOD);
	if (MEM_SIZE < processus2->pc)
		processus2->pc = 0;
	ft_parrpush((void***)&corewar->proc, processus2);
}

void 	lfork(t_proc *processus, t_corewar *corewar)
{
	void 			*tmp;
	unsigned int	p1;
	t_proc			*processus2;

	processus2 = (t_proc*)malloc(sizeof(t_proc));
	ft_memcpy(processus2, processus, sizeof(t_proc));
	processus->pc++;
	tmp = get_pc(processus, corewar);
	p1 = (unsigned int)tmp;
	processus2->pc = processus->pc + p1;
	if (MEM_SIZE < processus2->pc)
		processus2->pc = 0;
	ft_parrpush((void***)&corewar->proc, processus2);
}

void 	aff(t_proc *processus, t_corewar *corewar)
{
	char	aff;

	processus->pc += 2;
	aff = (char)get_reg_value(processus, corewar);
	ft_putchar(aff);
}
