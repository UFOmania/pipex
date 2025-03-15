CFLAGS = -Wall -Wextra -Wall -fsanitize=address -g3
NAME = pipex

LIBFT = _libft/libft.a

PRINTF = _printf/libftprintf.a

SRC =	src/pipex.c \
		src/parse.c\
		src/clear.c\
    

OBJ = $(SRC:.c=.o)

all: libft printf $(NAME)

printf:
	make -C _printf/

libft:
	make -C _libft/

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $@

src/%.o: src/%.c src/pipex.h
	cc $(CFLAGS) -c $< -o $@

clean:
	make clean -C _libft
	make clean -C _printf
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME) $(LIBFT) $(PRINTF)

re: fclean all