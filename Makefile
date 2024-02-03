ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME        :=	libft_malloc_${HOSTTYPE}.so

SRC_DIR     := 	src
OBJ_DIR     := 	obj
SRCS        := 	malloc.c \
				realloc.c \
				free.c \
				utils.c \
				ft_strlen.c \
				ft_putnbr_fd.c \
				ft_memcpy.c \

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
INCLUDE    := -I include

RM          := rm -rf
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -shared -g -fPIC $(CFLAGS) $(INCLUDE) -o $(NAME) $(SRCS)
		ln -sf $(NAME) libft_malloc.so
		$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		$(DIR_DUP)
		$(CC) $(CFLAGS) $(INCLUDE) -g -c -o $@ $<
		$(info CREATED $@)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME) libft_malloc.so obj

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: clean fclean re
.SILENT:

