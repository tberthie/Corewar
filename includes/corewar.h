/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:14:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/23 14:50:40 by tberthie         ###   ########.fr       */
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
# define E_DIFF "Champion size differs from the header"
# define E_SIZE "This champion exceeds size limit"
# define E_ARG "Invalid argument"
# define E_EXP "Argument expected"
# define E_NBR "Numbers must be positive and cannot overflow INT_MAX"
# define E_USAGE "./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."

typedef struct		s_champ {

	char			*name;
	char			*comment;
	char			*aff;
	int				number;

	unsigned int	size;
	void			*content;

	unsigned int	color;

}					t_champ;

typedef struct		s_proc {

	t_champ				*champ;
	unsigned int		*reg;
	int					pc;
	char				carry;

	char				safe;
	unsigned int		live;
	unsigned int		wait;

	struct s_corewar	*corewar;

}					t_proc;

typedef struct		s_corewar {

	void			*memory;
	t_proc			**proc;

	unsigned int	dump;
	unsigned int	next;

	t_champ			**champs;

	unsigned int	cycle;
	unsigned int	tot_cycle;
	unsigned int	ctd;
	int				check;
	int				last_alive;

	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*sf;
	TTF_Font		*hex_font;
	TTF_Font		*font;
	TTF_Font		*subfont;

	char			visual;
	char			play;
	unsigned int	*color;
	unsigned int	cps;
	unsigned int	step;

}					t_corewar;

void				setup(t_corewar *corewar, char **args);
void				load(t_corewar *corewar);
void				run(t_corewar *corewar);
void				process(t_corewar *corewar);

void				setup_visual(t_corewar *corewar);
void				visual_run(t_corewar *corewar);
SDL_Rect			rec(int x, int y, int w, int h);
void				render_hex(t_corewar *corewar);
void				dhex(t_corewar *cw, char *tx, unsigned int c, SDL_Rect rc);
void				text(t_corewar *cw, char *tx, unsigned int c, SDL_Rect rc);
void				subtext(t_corewar *cw, char *tx, SDL_Rect rc);
void				event(t_corewar *corewar);
void				render_stats(t_corewar *corewar);
void				set_visual(t_corewar *corewar);
void				set_ctd(t_corewar *corewar, unsigned int cycle);
void				display(t_corewar *corewar);
void				live_bar(t_corewar *corewar);

t_champ				*get_champ(t_corewar *corewar, int number);
void				add_champion(t_corewar *corewar, char *path);
void				*parse_champion(int fd, char *path);
char				find_champion(t_champ **champs, int n);
void				cycles(t_corewar *corewar, t_proc *proc);
char				alive_proc(t_proc **proc);
unsigned int		check_live(t_corewar *corewar);
void				dump(t_corewar *corewar);

void				error(char *file, char *msg);
unsigned int		rev_int(unsigned int nb);
void				hex_dump(unsigned char hex);
unsigned int		multi_color(unsigned int color, double ratio);

int					*byte_analysis(void *adr);
int					get_direct_value(unsigned char op, void *adr, t_proc *proc);
int					get_reg_value(t_proc *processus, void *adr);
int					get_indirect_value(t_proc *processus, void *adr);
int					get_value(t_proc *proc, int nbr, unsigned char op,
					void *adr);
int					get_indirect_value_nm(t_proc *processus, void *adr);
int					get_value_nm(t_proc *proc, int nbr, unsigned char op,
					void *adr);
void				live(t_proc *proc, t_corewar *corewar);
void				*get_pc(int	index, t_corewar *corewar);
void				c_and(t_proc *proc, t_corewar *corewar, unsigned char op);
void				c_or(t_proc *proc, t_corewar *corewar, unsigned char op);
void				c_xor(t_proc *proc, t_corewar *corewar, unsigned char op);
void				ld(t_proc *proc, t_corewar *corewar, unsigned char op);
void				lld(t_proc *proc, t_corewar *corewar, unsigned char op);
void				ldi(t_proc *proc, t_corewar *corewar, unsigned char op);
void				lldi(t_proc *proc, t_corewar *corewar, unsigned char op);
void				st(t_proc *proc, t_corewar *corewar);
void				sti(t_proc *proc, t_corewar *corewar, unsigned char op);
int					set_index(void *adr);
void				add(t_proc *proc, t_corewar *corewar);
void				sub(t_proc *proc, t_corewar *corewar);
void				zjmp(t_proc *proc, t_corewar *corewar);
void				c_fork(t_proc *proc, t_corewar *corewar, unsigned char op);
void				lfork(t_proc *proc, t_corewar *corewar, unsigned char op);
void				aff(t_proc *proc, t_corewar *corewar);
int					get_int_direct_value(void *adr, t_proc *processus);
int					get_int_indirect_value(void *adr, t_proc *processus);
void				print_bit(t_corewar *corewar, int pc, int p1);
unsigned int		set_pc(int tmp);
void				change_carry(t_proc *processus, int p1);
int					move_pc(int	tab, unsigned char op);
void				return_error(t_proc *processus, int *tab);
void				*set_adr(void *adr, t_proc *processus);

#endif
