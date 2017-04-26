/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/26 19:16:56 by tberthie         ###   ########.fr       */
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
# define GREEN "\x1b[32m"
# define EOC "\x1b[0m"

# define E_FORMAT "Not a valid champion file"
# define E_READ "Invalid champion file"
# define E_SIZE "This champion exceeds size limit"
# define E_ARG "Invalid argument"
# define E_EXP "Argument expected"
# define E_NBR "Bad number syntax (> 0 expected)"
# define E_USAGE "./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."

typedef struct		s_champ {

	char			*name;
	char			*comment;
	unsigned int	number;

	unsigned int	size;
	void			*content;

}					t_champ;

typedef struct		s_proc {

	void			*reg[REG_NUMBER];
	void			*pc;
	char			carry;

	char			alive;
	unsigned int	live;

}					t_proc;

typedef struct		s_corewar {

	void			*memory;
	t_proc			**proc;

	unsigned int	dump;
	unsigned int	next;

	t_champ			**champs;

	unsigned int	cycle;
	unsigned int	ctd;
	unsigned int	check;

	unsigned int	last_alive;

}					t_corewar;

void				setup(t_corewar *corewar, char **args);
void				load(t_corewar *corewar);
void				run(t_corewar *corewar);
void				process(t_corewar *corewar);

void				add_champion(t_corewar *corewar, char *path);
void				*parse_champion(int fd, char *path);
char				find_champion(t_champ **champs, unsigned int n);

void				error(char *file, char *msg);
unsigned int		rev_int(unsigned int nb);
void				hex_dump(unsigned char hex);

#endif
