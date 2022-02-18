##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-malloc-jeffrey.winkler
## File description:
## Makefile
##

SRC					=	src/malloc.c		\
						src/realloc.c		\
						src/memory.c		\
						src/block.c			\
						src/best_fit.c		\
						src/utils.c

INC_DIR				=	./include

CFLAGS				+=	-Wall -Wextra -I$(INC_DIR) -fpic

OBJ					=	$(SRC:.c=.o)

NAME				=	libmy_malloc.so

all: $(NAME)

$(NAME): $(OBJ)
	gcc -shared $(CFLAGS) -o $(NAME) $(OBJ)

error: CFLAGS += -Werror
error: re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
