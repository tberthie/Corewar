/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:41:31 by ramichia          #+#    #+#             */
/*   Updated: 2017/04/24 21:07:47 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"


void 	aff(int registre)
{
	int		c;

	c = registre % 256;
	ft_putchar(c);
}

void 	and(char *p1, char *p2, void *p3) // les arguments p1 et p2 sont des chaines de caractere en binaire (ex: 0x00 0x0f) ou je considere qu on aura deja decoupé la chaine de caractère initiale (avec le numero de l'instruction, le bytecode et les arguments)
{                                         // void *p3 correspond a l'adresse d'un registre
	char	**tab1;
	char	**tab2;
	int		r1;
	int		r2;

	tab1 = ft_strsplit(p1, " "); // je ne sais pas encore comment je vais recevoir p1, si c est une string ou un int en hexa, je pars du principe que c est une string (ex: "0x00 0xff")
	tab2 = ft_strsplit(p2, " ");
	if (!tab1[1])
		r1 = tab1[0]; // il faudra encore modifier la string en hexa avec une fonction autre que atoi ou itoa qui ne prennent que des decimals en entrée (je l ai pas encore codé)
	else
		r1 = tab1[0]| tab1[1];
	if (!tab2[1])
		r2 = tab2[0];
	else
		r2 = tab2[0]| tab2[1];

	p3 = r1 & r2;
}

void 	ld(char *p1, void *p2) // P2 est l'adresse d un registre, p1 une valeur (ex: 0x22) ou un registre(dans ce cas il faudra récupérer la valeur de ce registre)
{
	void 	*adr;

	*adr = PC + (p1 % IDX_MOD); // pareil il faudra modifier p1 (string en hexa) em int, la je donne une adresse a un pointeur
	p2 = ft_memncpy(*adr, p2, REG_SIZE); // on copie REG_SIZE octets de adr vers p2;
}

void 	st(void *p1, char *p2)
{
	void 	*adr;
	*adr = PC + (p2 % IDX_MOD); // je donne une adresse a un pointeur

	adr = p2; // on stocke la valeur p2 (a transofrmer en int) a l adresse adr
}
