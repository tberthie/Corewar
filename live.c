/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:41:31 by ramichia          #+#    #+#             */
/*   Updated: 2017/04/28 18:48:52 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// s assurer qu il ny ait pas d overflow (on ne depasse pas corewar->memory + MEM_SIZE)
// il faudra ajouter la modification du carry
// stocker le numero du dernier joueur à envoyer live (voir struct Corewar)
// avancer la tete de lecture(pc) de la taille de l'instruction (prendre en compte l'octet de codage)

#include "corewar.h"

void		modify_carry(t_proc processus)
{
	if (processus->carry == 1)
		processus->carry = 0;
	else
		processus->carry = 1;
}

void 	load_size(char *src, void *dest, int size, int *mv)
{
	char 	*tmp;

	tmp = ft_memalloc(size);
	*tmp = *tmp | *src;
	dest = ft_strdup(tmp);
	*mv++;
}

void 	aff(int registre)
{
	int		c;

	c = registre % 256;
	ft_putchar(c);
}

void 	or(int *p1, int *p2, int p3, t_proc *processus) // les arguments p1 et p2 sont des ints en hexa(venant du binaire)
{                                    					 // void *p3 correspond a l'adresse d'un registre
	unsigned int r1;
	unsigned int r2;

	r1 = get_value(p1, processus);
	r2 = get_value(p2, processus);
	*processus->reg[p3] = (char*)(r1 | r2); // en fonction de la "forme" des void*, cette ligne sera à modifier
}

void 	xor(int *p1, int *p2, int p3, t_proc *processus) // les arguments p1 et p2 sont des ints en hexa(venant du binaire)
{                                     						// void *p3 correspond a l'adresse d'un registre
	unsigned int r1;
	unsigned int r2;

	r1 = get_value(p1, processus);
	r2 = get_value(p2, processus);
	*processus->reg[p3] = (char*)(r1 ^ r2); // en fonction de la "forme" des void*, cette ligne sera à modifier
}

void 	lldi(int *p1, int *p2, int p3, t_proc *processus, t_corewar *corewar)
{
	unsigned int	r1;
	unsigned int	r2;
	unsigned int	S;
	void 	*adr;
	int		i;

	i = 0;
	S = 0;
	r1 = get_value(p1, processus);
	r2 = get_value(p2, processus);
	while (i < IND_SIZE)
	{
		S =  S + (char)*adr;
		adr ++;
		i++;
	}
	S = S + r2;
	adr = processus->pc + S;
	if ((char)corewar->memory < (char)adr)
		adr = corewar->memory;
	load_size(adr, processus->reg[p3], REG_SIZE);
	modify_carry(processus);
}


void 	sub(int r1, int r2, int r3, t_proc *processus)
{
	processus->reg[r3] = (unsigned int)processus->reg[r1] - (unsigned int)processus->reg[r2];
}
