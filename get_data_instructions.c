/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:00:50 by ramichia          #+#    #+#             */
/*   Updated: 2017/04/28 22:02:02 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void 	*move_adr(void *adr, t_corewar *corewar, int nbr, int *mv)
{
	adr += nbr;
	*mv += nbr;
	if ((char)corewar->memory + MEM_SIZE < (char)adr)
		adr = corewar->memory;
	return(adr);

}

void 	and(t_proc *processus, t_corewar *corewar)
{
	char	*p1;
	char	*p2;
	int		mv;
	int		*tab;
	void 	*tmp;

	mv = 0;
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 1, &mv); // on passe le numero de l instruction et l octet de codage
	tab = byte_analysis(tmp, &mv);
	tmp++;
	p1 = get_value(tmp, tab[0], &mv, processus); // on recupere le premier argument
	tmp = processus->pc + mv; // on deplace tmp em fonction de la taille du premier argument
	p2 = get_value(processus, tab[1], &mv, processus);
	tmp = processus->pc + mv;
	load_size(p1 & p2, processus->reg[(char)*tmp], REG_SIZE, &mv)
	modify_carry(processus);
	processus->pc += mv;
}

void 	ld(t_proc *processus, t_corewar *corewar) // p2 est le numero d un registre, p1 est une valeur ou un registre
{
	char	*p1;
	void 	*tmp;
	void 	*adr;
	int		mv;
	int		*tab;

	mv = 0;
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 1, &mv);
	tab = byte_analysis(tmp, &mv);
	p1 = get_value(tmp, tab[0], &mv, processus);
	tmp = processus->pc + mv;
	load_size(p1, processus->reg[(char)*tmp], REG_SIZE, &mv); // verifier si c est la bonne maniere d ecrire dans un registre
	modify_carry(processus);
	processus->pc += mv;
}

void 	ldi(t_proc *processus, t_corewar *corewar)
{
	int		*tab;
	int		mv;
	void 	*tmp;
	char	*p1;

	mv = 0;
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 1, &mv);
	tab = byte_analysis(tmp, &mv);
	tmp++;
	p1 = get_value(tmp, tab[0], &mv, processus);
	tmp = processus->pc + mv;
	p1 = p1 | get_value(tmp, tab[1], &mv, processus);
	tmp = processus->pc + mv;
	load_size(p1, processus->reg[(char)*tmp], REG_SIZE, &mv);
	modify_carry(processus);
	processus->pc += mv;
}

void 	st(t_proc *processus, t_corewar *corewar)
{
	void 	*tmp;
	int		mv;
	char	*p1;
	void	*p2;
	int		*tab;

	mv = 0;
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 1, &mv);
	tab = byte_analysis(tmp, &mv);
	tmp++;
	p1 = get_reg_value(tmp, processus, &mv);
	tmp = processus->pc + mv;
	p2 = get_adr_modulo(get_value(tmp, processus, &mv), processus, tab[1], &mv);
	load_size(p1, p2, REG_SIZE, &mv);
	processus->pc += mv;
}

void 	sti(t_proc *processus, t_corewar *corewar)
{
	int		*tab;
	int		mv;
	char	*p1;
	char 	*p2;
	char 	*p3;

	processus->pc = move_adr(processus->pc, corewar, 1, &mv);
	tab = byte_analysis(processus->pc, &mv);
	processus->pc++;
	mv = 0;
	p1 = get_value(processus->pc, tab[0], &mv, processus);
	processus->pc += mv;
	mv = 0;
	p2 = get_value(processus->pc, tab[1], &mv, processus);
	processus->pc += mv;
	p3 = get_value(processus->pc, tab[2], &mv, processus);
	load_size(p1, corewar->memory + char(p2 | p3), REG_SIZE, &mv); // voir si il faut vraiment avancer mv a ce moment la, de combien?
	processus->pc++; // voir si il faut vraiment avancer mv a ce moment la, de combien?
}

void 	add(t_proc *processus, t_corewar *corewar)
{
	void 	*tmp;
	int		mv;
	int		*tab;
	char 	*p1;
	char 	*p2;

	mv = 0;
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 2, &mv);
	p1 = get_value(tmp, 1 , &mv, processus);
	tmp = processus->pc + mv;
	p1 = p1 | get_value(tmp, 1 , &mv, processus);
	tmp = processus->pc + mv;
	load_size(p1, &processus->reg[(char)*tmp], REG_SIZE, &mv);
	modify_carry(processus);
	processus->pc += mv;
}

void 	zjmp(t_proc *processus, t_corewar *corewar)
{
	void 	*tmp;
	int		mv;
	char 	*p1;

	mv = 0;
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 1, &mv);
	p1 = (char)*tmp;
	if (processus->carry == 1)
		processus->pc = processus->pc + (p1 % IDX_MOD);
	mv++;
	processus->pc += mv;
}

void 	fork(t_proc *processus, t_corewar *corewar)
{
	void 	*tmp;
	int		mv;
	char 	p1;
	t_proc	*processus2;

	mv = 0;
	processus2 = (t_proc*)malloc(sizeof(t_proc));
	processus2 = ft_memcpy(processus2, processus, sizeof(t_proc));
	tmp = processus->pc;
	tmp = move_adr(tmp, corewar, 1, &mv);
	p1 = (char)*tmp;
	processus2->pc = processus->pc + (p1 % IDX_MOD);
	if ((char)corewar->memory + MEM_SIZE < (char)processus2->pc)
		processus2->pc = corewar->memory;
	ft_parrpush(corewar->proc, processus2);
}

// void 	aff(t_proc *processus, t_corewar *corewar)
// {
// 	void 	*tmp;
// 	int		mv;
// 	char 	*p1;
//
// 	mv = 0;
// 	tmp = processus->pc;
// 	tmp = move_adr(tmp, corewar, 2, &mv);
// 	p1 = get_value(tmp, &mv);
// 	tmp = processus->pc + mv;
// }
