# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 13:06:49 by tberthie          #+#    #+#              #
#    Updated: 2017/04/27 16:55:31 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = $(addsuffix .o, $(addprefix objs/, main \
	   load setup setup_champions \
	   run process \
	   utl))

NAME = corewar

all: objs $(NAME)

$(NAME): $(OBJS)
	make -C libft
	gcc -o $(NAME) $(OBJS) libft/libft.a

objs:
	mkdir objs

objs/%.o: srcs/%.c
	gcc -c $< -o $@ -I includes -I libft -Wall -Wextra -O3

clean:
	make clean -C libft
	rm -rf objs

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all
