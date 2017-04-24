/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/24 17:46:01 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"

# define RED "\x1b[31m"
# define EOC "\x1b[0m"

# define E_FORMAT	"Not a valid champion file"
# define E_OPEN		"Invalid file"
# define E_READ		"Failed to read the file"
# define E_SIZE		"This champion exceeds size limit"

typedef struct		s_champ {

	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		number;

}					t_champ;

typedef struct		s_corewar {

	void				*memory;
	unsigned int		dump;
	char				pad[4];

}					t_corewar;

char				setup(t_corewar *corewar, char **args);

unsigned int		rev_int(unsigned int nb);

#endif
