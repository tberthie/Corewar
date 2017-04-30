/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/04/30 14:14:06 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/libft.h"

void 	*get_adr_reg(t_proc *processus, t_corewar *corewar)
{
	unsigned int	index;
	void 	*adr;

	adr = get_pc(processus, corewar);
	index = (unsigned int)adr;
	return(processus->reg[index]);
}

void 	*get_adr_dir_modulo(t_proc *processus, t_corewar *corewar)
{
	void 	*adr;
	void 	*tmp;
	char	index;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp += DIR_SIZE;
	index = (char)tmp;
	processus->pc += DIR_SIZE;
	return(adr + (index % IDX_MOD));
}

void 	*get_adr_modulo(t_proc *processus, t_corewar *corewar, int nbr)
{
	if (nbr == 1)
		return(get_adr_reg(processus, corewar));
	else
		return(get_adr_dir_modulo(processus, corewar));
}

int		*byte_analysis(t_proc *processus, t_corewar *corewar)
{
	int		*nbr;
	void 	*adr;
	char	byte;

	adr = get_pc(processus, corewar);
	byte = (char)adr;
	nbr = (int*)malloc(sizeof(int) * 3);
	nbr[0] = (byte & 11000000) >> 6;
	nbr[1] = (byte & 00110000) >> 4;
	nbr[2] = (byte & 00001100) >> 2;
	processus->pc++;
	return(nbr);
}

char	*get_direct_value(t_proc *processus, t_corewar *corewar) // a modifier car peut se lire sur 2 ou 4 octets
{
	char	*value;
	void 	*adr;

	adr = get_pc(processus, corewar);
	adr += 3;
	value = (char*)adr;
	processus->pc += DIR_SIZE;
	return(value);
}

// char	*get_direct_value(t_proc *processus, t_corewar *corewar) // a modifier car peut se lire sur 2 ou 4 octets
// {
// 	char	*value;
// 	void 	*adr;
//
// 	adr = get_pc(processus, corewar);
// 	adr += 3;
// 	value = (char*)adr;
// 	processus->pc += DIR_SIZE;
// 	return(value);
// }

char 	*get_indirect_value_nm(t_proc *processus, int size, t_corewar *corewar)
{
	char	index;
	void 	*adr;
	void 	*tmp;
	char 	*value;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp++;
	index = (char)tmp;
	value = ft_memalloc(size);
	ft_memcpy(value, adr + index , size);
	processus->pc += IND_SIZE;
	return(adr);
}

char 	*get_indirect_value(t_proc *processus, int size, t_corewar *corewar)
{
	char	index;
	void 	*adr;
	void 	*tmp;
	char 	*value;

	adr = get_pc(processus, corewar);
	tmp = adr;
	tmp++;
	index = (char)tmp;
	value = ft_memalloc(size);
	ft_memcpy(value, adr + (index % IDX_MOD), size);
	processus->pc += IND_SIZE;
	return(adr);
}

char	*get_reg_value(t_proc *processus, t_corewar *corewar)
{
	unsigned int	index;
	void 	*adr;
	char	*value;

	adr = get_pc(processus, corewar);
	index = (unsigned int)adr;
	value = ft_memalloc(REG_SIZE);
	ft_memcpy(value , processus->reg[index] , REG_SIZE);
	processus->pc++;
	return(value);
}

char	*get_value(t_proc *processus, t_corewar *corewar, int size, int nbr)
{
	char	*p1;

	if (nbr == 10)
		p1 = get_direct_value(processus, corewar);
	else if (nbr == 11)
		p1 = get_indirect_value(processus, size, corewar);
	else
		p1 = get_reg_value(processus,corewar);
	return(p1);
}

char	*get_value_nm(t_proc *processus, t_corewar *corewar, int size, int nbr)
{
	char	*p1;

	if (nbr == 10)
		p1 = get_direct_value(processus, corewar);
	else if (nbr == 11)
		p1 = get_indirect_value_nm(processus, size, corewar);
	else
		p1 = get_reg_value(processus,corewar);
	return(p1);
}
