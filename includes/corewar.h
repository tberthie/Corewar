/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/03 17:40:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "config.h"

# include "SDL.h"
# include "SDL_ttf.h"

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

	unsigned int	color;

}					t_champ;

typedef struct		s_proc {

	void			*(reg[REG_NUMBER]);
	int				pc;
	char			carry;

	char			alive;
	unsigned int	live;
	unsigned int	wait;

}					t_proc;

typedef struct		s_visual {

	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*sf;
	TTF_Font		*hex_font;
	TTF_Font		*font;

	void			*save;
	unsigned int	color[MEM_SIZE];
	unsigned int	cps;
	unsigned int	step;

}					t_visual;

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

	char			visual;
	char			play;

}					t_corewar;

void				setup(t_corewar *corewar, char **args);
void				load(t_corewar *corewar);
void				run(t_corewar *corewar);
void				process(t_corewar *corewar, t_visual *visu);

void				setup_visual(t_visual *visu);
void				visual_run(t_corewar *corewar, t_visual *visu);
SDL_Rect			rec(int x, int y, int w, int h);
void				render_hex(t_corewar *corewar, t_visual *visu);
void				dhex(t_visual *visu, char *tx, unsigned int c, SDL_Rect rc);
void				text(t_visual *visu, char *tx, unsigned int c, SDL_Rect rc);
void				event(t_corewar *corewar, t_visual *visu);
void				render_stats(t_corewar *corewar, t_visual *visu);

t_champ				*get_player(t_corewar *corewar, t_proc *proc);
void				add_champion(t_corewar *corewar, char *path);
void				*parse_champion(int fd, char *path);
char				find_champion(t_champ **champs, unsigned int n);
void				cycles(t_corewar *corewar, t_proc *proc);
char				alive_proc(t_proc **proc);
unsigned int		check_live(t_corewar *corewar, t_visual *v, t_proc **proc);

void				error(char *file, char *msg);
unsigned int		rev_int(unsigned int nb);
void				hex_dump(unsigned char hex);

int			*byte_analysis(t_proc *processus, t_corewar *corewar);
int			get_direct_value(t_proc *processus, t_corewar *corewar, unsigned char op);
int			get_indirect_value(t_proc *processus, t_corewar *corewar);
int			get_reg_value(t_proc *processus, t_corewar *corewar);
int			get_value(t_proc *processus, t_corewar *corewar, int nbr, unsigned char op);
int			get_indirect_value_nm(t_proc *processus, t_corewar *corewar);
int			get_value_nm(t_proc *proc, t_corewar *cr, int nbr, unsigned char op);
void		live(t_proc *processus, t_corewar *corewar);
void		*get_pc(t_proc *processus, t_corewar *corewar);
void		c_and(t_proc *processus, t_corewar *corewar, unsigned char op);
void		c_or(t_proc *processus, t_corewar *corewar, unsigned char op);
void		c_xor(t_proc *processus, t_corewar *corewar, unsigned char op);
void		ld(t_proc *processus, t_corewar *corewar, unsigned char op);
void		lld(t_proc *processus, t_corewar *corewar, unsigned char op);
void		ldi(t_proc *processus, t_corewar *corewar, unsigned char op);
void		lldi(t_proc *processus, t_corewar *corewar, unsigned char op);
void		st(t_proc *processus, t_corewar *corewar);
void		sti(t_proc *processus, t_corewar *corewar, unsigned char op);
int			set_index(t_proc *processus, t_corewar *corewar);
void		add(t_proc *processus, t_corewar *corewar);
void		sub(t_proc *processus, t_corewar *corewar);
void		zjmp(t_proc *processus, t_corewar *corewar, unsigned char op);
void		c_fork(t_proc *processus, t_corewar *corewar);
void		lfork(t_proc *processus, t_corewar *corewar);
void		aff(t_proc *processus, t_corewar *corewar);

#endif
