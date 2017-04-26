/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/26 13:51:02 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"

# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>

# define RED "\x1b[31m"
# define EOC "\x1b[0m"

# define E_FORMAT "Not a valid champion file"
# define E_READ "Invalid champion file"
# define E_SIZE "This champion exceeds size limit"
# define E_ARG "Invalid argument"
# define E_USAGE "./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."

typedef struct		s_champ {

	char				*name;
	char				*comment;
	unsigned int		number;

	void				*reg[REG_NUMBER];

	unsigned int		size;
	void				*content;

}					t_champ;

typedef struct		s_corewar {

	void				*memory;
	unsigned int		dump;
	char				pad[4];
	t_champ				**champs;

}					t_corewar;

void				setup(t_corewar *corewar, char **args);
void				add_champion(t_corewar *corewar, char *path);
void				*parse_champion(int fd, char *path);

void				error(char *file, char *msg);

unsigned int		rev_int(unsigned int nb);

#endif
