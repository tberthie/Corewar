# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 13:06:49 by tberthie          #+#    #+#              #
#    Updated: 2017/05/23 14:58:54 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = $(addsuffix .o, $(addprefix objs/, main \
	   load setup setup_champions \
	   run process operations operations2 operations3 \
	   instructions1 instructions2 instructions3 instructions4 \
	   visual event draw render stats bar \
	   utl))

NAME = corewar

all: objs $(NAME)

$(NAME): $(OBJS)
	make -C libft
	gcc -o $(NAME) $(OBJS) libft/libft.a \
	SDL/libSDL2-2.0.0.dylib SDL/libSDL2_ttf-2.0.0.dylib

objs:
	mkdir objs

objs/%.o: srcs/%.c
	gcc -c $< -o $@ -I includes -I libft -I SDL -Wall -Wextra -Werror -O3

clean:
	make fclean -C libft
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all
