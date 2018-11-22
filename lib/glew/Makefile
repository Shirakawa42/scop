# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 15:48:19 by lvasseur          #+#    #+#              #
#    Updated: 2018/11/22 15:48:21 by lvasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = glew.a

SRC = glew.c

all: $(NAME)

$(NAME): 
	@gcc -c $(SRC)
	@ar rc $(NAME) $(SRC:.c=.o)

clean:
	@rm -f $(SRC:.c=.o)

fclean: clean
	@rm -f $(NAME)

re: fclean all
