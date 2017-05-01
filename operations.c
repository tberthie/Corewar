/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/05/01 16:30:12 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// il faut que je recupere des int dans toutes les fonctions et que je gere la suite dans chacune des instructions
#include "../includes/corewar.h"
#include "../libft/libft.h"


int        *byte_analysis(t_proc *processus, t_corewar *corewar)
{
    int		*nbr;
    void 	*adr;
    char	byte;

    adr = get_pc(processus, corewar);
    byte = *(unsigned char*)adr;
    nbr = (int*)malloc(sizeof(int) * 3);
    nbr[0] = (byte >> 6) & (REG_CODE | DIR_CODE | IND_CODE);
    nbr[1] = (byte >> 4) & (REG_CODE | DIR_CODE | IND_CODE);
    nbr[2] = (byte >> 2) & (REG_CODE | DIR_CODE | IND_CODE);
    processus->pc++;
    return(nbr);
}


int 	get_direct_value(t_proc *processus, t_corewar *corewar) // a modifier car peut se lire sur 2 ou 4 octets
{
	char	index;
	void 	*adr;
	// int		value;

	index = *(char*)(corewar->memory + processus->pc + 3);
	// adr = get_pc(processus, corewar);
	// adr += 3;
	// index = (char)adr;
	// value = (int)(corewar->memory + index);
	processus->pc += DIR_SIZE;
	return((int)index);
}

int		get_indirect_value(t_proc *processus, t_corewar *corewar)
{
	void 	*adr;
	void 	*tmp;
	int		value;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp++;
	adr = corewar->memory + processus->pc + (int)tmp % IDX_MOD;
	value = (int)adr;
	processus->pc += IND_SIZE;
	return(value);
}

int		get_reg_value(t_proc *processus, t_corewar *corewar)
{
	char	index;
	int		value;

	index = *(char*)(corewar->memory + processus->pc);
	value = (int)processus->reg[index];
	processus->pc++;
	return(value);
}

int		get_value(t_proc *processus, t_corewar *corewar, int nbr)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(processus, corewar);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value(processus, corewar);
	else
		p1 = get_reg_value(processus,corewar);

	return(p1);
}

int		get_indirect_value_nm(t_proc *processus, t_corewar *corewar)
{
	void 	*adr;
	void 	*tmp;
	int		value;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp++;
	adr = corewar->memory + processus->pc + (int)tmp;
	value = (int)adr;
	processus->pc += IND_SIZE;
	return(value);
}

int		get_value_nm(t_proc *processus, t_corewar *corewar, int nbr)
{
	int		p1;

	if (nbr == DIR_CODE)
		p1 = get_direct_value(processus, corewar);
	else if (nbr == IND_CODE)
		p1 = get_indirect_value_nm(processus, corewar);
	else
		p1 = get_reg_value(processus,corewar);

	return(p1);
}
