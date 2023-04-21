##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC   =	colls_generator.c 			\

OBJ =   $(SRC:.c=.o)


CFLAGS = -Wall -Wextra -Werror

NAME =  colls_maker

all:    $(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(SRC)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f *.log

re: fclean all
