SRC=$(addsuffix .c, main error init check_inst check_inst_1 check_inst_2 \
	check_inst_3 check_inst_4 store_asm copy_hex check header offset \
	store_tools aff print_hex print_off print_header print_aff print_bytes \
	print_dir print_off_int check_tools store_tools_2 offset_tools)
OBJ=$(addprefix obj/,$(SRC:.c=.o))
NAME=asm
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
