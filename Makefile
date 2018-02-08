NAME = scop

SRC =	src/main.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./includes

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -lm

c clean:
	rm -f $(OBJ)
	@make clean -C libft/

f fclean: clean
	rm -f $(NAME)
	@make fclean -C libft/

r re: fclean all

g good: $(NAME) clean
