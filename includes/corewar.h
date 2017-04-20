/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/20 15:18:07 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"

typedef struct		s_champ {

	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		number;

}					t_champ;

typedef struct		s_corewar {

	void				*memory;
	unsigned int		dump;

}					t_corewar;

char				setup(t_corewar *corewar, char **args);

#endif
