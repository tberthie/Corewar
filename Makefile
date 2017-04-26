# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 13:06:49 by tberthie          #+#    #+#              #
#    Updated: 2017/04/26 17:38:24 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = $(addsuffix .o, $(addprefix objs/, main setup bits utl setup_champions \
	   load run))
NAME = corewar
FLAGS = -Weverything -O3 \
		-Wno-pointer-arith -Wno-padded -Wno-missing-noreturn


all: objs $(NAME)

$(NAME): $(OBJS)
	make -C libft
	gcc -o $(NAME) $(OBJS) libft/libft.a

objs:
	mkdir objs

objs/%.o: srcs/%.c
	gcc $(FLAGS) -o $@ -c $< -I includes -I libft

clean:
	make clean -C libft
	rm -rf objs

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all
