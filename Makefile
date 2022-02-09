##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-malloc-jeffrey.winkler
## File description:
## Makefile
##

SRC					=	src/malloc.c		\
						src/memory.c		\
						src/block.c			\
						src/best_fit.c

DEBUG_SRC			=	debug/debug.c

INC_DIR				=	./include

CFLAGS				+=	-Wall -Wextra -I$(INC_DIR) -fpic

OBJ					=	$(SRC:.c=.o)
DEBUG_OBJ			=	$(DEBUG_SRC:.c=.o)

NAME				=	libmy_malloc.so

all: $(NAME)

$(NAME): $(OBJ)
	gcc -shared $(CFLAGS) -o $(NAME) $(OBJ)

error: CFLAGS += -Werror
error: re

debug: clean
debug: $(DEBUG_OBJ)
debug: OBJ += $(DEBUG_OBJ)
debug: all

info: CFLAGS += -g -D DEBUG=1
info: debug

log: CFLAGS += -g -D DEBUG=5
log: debug

to_much_debug: CFLAGS += -g -D DEBUG=10
to_much_debug: debug

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all