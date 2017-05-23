OBJ=$(addprefix ft_,$(addsuffix .o,\
	atoi atoip itoa itoabase utoabase abs\
	freeret freeswap memalloc memcpy m ptrswap free memset\
	gnl rfc gdc\
	isdir\
	putchar putnchar putnbr putstr\
	strchr strrchr strstr strcmp strncmp stricmp strcpy strdup strndup strjoin strcjoin strsjoin strsplit\
	strlen strrem strfrmchr strcount\
	strnew strpush strspush strins strsins strrem\
	strarrdup strarrstr strarrstrn strarrrem strarrstrlen strarrstrstrr\
	parrnew parrfree parrelmfree parrpush parrprem parrrem parrlen parrdup parrndup parrjoin\
	intlen\
	print\
	))

PRF=$(addprefix printf/ft_,$(addsuffix .o,\
	printf con format cast utl wchar wutl color))

NAME=libft.a

all: $(NAME)

$(NAME): $(OBJ) $(PRF)
	ar rc $(NAME) $(OBJ) $(PRF)

%.o: %.c
	gcc -c $< -o $@ -Wall -Wextra -Werror -O3 -I .

clean:
	rm -f $(OBJ)
	rm -f $(PRF)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
