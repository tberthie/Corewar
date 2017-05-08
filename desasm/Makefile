SRC=$(addsuffix .c, main error init print print_1 get_header)
OBJ=$(addprefix obj/,$(SRC:.c=.o))
NAME=desasm
LIBFT=libft/libft.a
WFLAGS= -Werror -Wall -Wextra

.PHONY: clean fclean re all lib dobj

all: lib dobj $(NAME)

lib:
	make -C libft

dobj:
	mkdir -p obj

$(NAME): $(LIBFT) $(OBJ)
	gcc $(OBJ) -o $@ -L./libft -lft $(WFLAGS)

obj/%.o: srcs/%.c
	gcc -o $@ -c $< -I./includes $(WFLAGS)

clean:
	rm -rf obj
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
