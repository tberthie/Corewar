/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramichia <ramichia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:43 by ramichia          #+#    #+#             */
/*   Updated: 2017/04/28 21:41:36 by ramichia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void 	*get_adr_reg(char *value, int *mv, t_proc *processus)
{
	char	index;

	index = (char)*value;
	*mv++;
	return(&processus->reg[index]);
}

void 	*get_adr_dir_modulo(char *value, int *mv, t_proc *processus)
{
	void 	*adr;

	adr = processus->pc + (value % IDX_MOD);
	*mv += 2;
	return(adr);
}

void 	*get_adr_modulo(char *value, t_proc *processus, int nbr, int *mv)
{
	if (nbr == 1)
		return(get_adr_reg(value, mv, processus));
	if (nbr == 11)
		return(get_adr_dir_modulo(value, mv, processus));
}

int		*byte_analysis(void *adr, int *mv)
{
	char	value;
	int		nbr[3];

	value = (char)*tmp;
	nbr[0] = (value & 11000000) >> 6;
	nbr[1] = (value & 00110000) >> 4;
	nbr[2] = (value & 00001100) >> 2;
	*mv++;
	return(nbr);
}

char	*get_direct_value(void *tmp, int *mv)
{
	char	*value;

	tmp += 3;
	*mv += 3; // trouver comment savoir de combien il faut avancer
	*value = (char)*tmp;
	*mv++;
	return(value);
}

char 	*get_indirect_value(void *tmp, t_proc *processus, int *mv)
{
	char	index;
	char 	*adr;

	tmp ++;
	*mv ++; // trouver comment savoir de combien il faut avancer
	index = (char)*tmp;
	adr = ft_memalloc(IND_SIZE);
	ft_memcpy(adr , processus->pc + index, IND_SIZE);
	*mv++;
	return(adr);
}

char	*get_reg_value(void *tmp, t_proc *processus, int *mv)
{
	char	index;
	void 	*adr;

	index = (char)*tmp;
	adr = ft_memalloc(REG_SIZE);
	ft_memcpy(adr , processus->pc + index, REG_SIZE);
	*mv++;
	return((char*)adr);
}

char	*get_value(void *tmp, , int nbr, int *mv, t_proc *processus)
{
	char	*p1;

	if (nbr == 10)
		p1 = get_direct_value(tmp, mv);
	else if (nbr == 11)
		p1 = get_indirect_value(tmp, processus, mv);
	else if (nbr == 1)
		p1 = get_reg_value(tmp, processus, mv);
	return(p1);
}
