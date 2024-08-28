NAME = minishell

HEADER = ./inc/

AUTHOR = nal-haki

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra -I $(HEADER) #-fsanitize=address

SRCS = j tree_utils utils variables path_cmd copy io execution binary_tree dsenv replace_var main

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

SHELL := /bin/bash

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

objs/%.o:	src/%.c
			@mkdir -p $(dir $@)
			@${CC} ${FLAGS} -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT) $(HEADER)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)
			@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(LIBFT):
			@make -C ./libft
			@printf "%-53b%b" "$(COM_COLOR)LIBFT Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"


clean:
			rm -rf objs/
			@make clean -C ./libft
			@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


fclean:		clean
				rm $(NAME)
				rm ./libft/libft.a
				@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY: 	all clean fclean re

.SILENT: 	clean fclean re all