/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 18:28:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/29 18:32:02 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "corewar.h"

int		*byte_analysis(t_proc *processus, t_corewar *corewar);
char	*get_value(t_proc *processus, t_corewar *corewar, int size, int nbr);
char	*get_reg_value(t_proc *processus, t_corewar *corewar);
void	*get_adr_modulo(t_proc *processus, t_corewar *corewar, int nbr);

#endif
