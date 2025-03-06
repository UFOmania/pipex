
CFLAGS = -Wall -Wextra -Werror
NAME=pipex
# CFLAGS = -fsanitize=address -g3

LIBFT = _libft/libft.a
PRINTF = _printf/libftprintf.a

SRC =	src/pipex.c\
		src/parser.c\
		src/execute.c\
		src/debuger.c\
		src/clean.c\

OBJ = $(SRC:.c=.o)


all: libft printf $(NAME)

libft:
	make -C _libft/

printf:
	make -C _printf/

$(NAME): $(OBJ) 
	cc $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJ) -o $@

src/%.o: %.c include/pipex.h
	cc $(CFLAGS) -c $<

clean:
	make clean -C _libft
	make clean -C _printf
	rm -rf $(OBJ)

re: fclean all

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(LIBFT)

