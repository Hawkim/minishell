# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 21:21:54 by nal-haki          #+#    #+#              #
#    Updated: 2024/09/22 16:24:06 by nal-haki         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
LIBFT			= libft.a
CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g
CINC 			= -I $(INCLUDE_PATH)
CREAD			= -lreadline
LIBFT_PATH 		= ./libft/
SRCS_PATH 		= ./src/
OBJS_PATH		= ./minishell_objects/
INCLUDE_PATH 	= ./include/

SRCS			= main.c init_tool.c builtin.c builtin_utils.c ft_cd.c ft_echo.c ft_env.c\
				  ft_exit.c ft_export.c ft_export_two.c ft_pwd.c ft_unset.c cmd_utils.c cmd.c\
				  exe_child.c execution.c hash.c keyy_search.c add_back_hash.c get_keyy.c\
				  get_value.c insert_hash.c expansion.c expansion_two.c expansion_tools.c\
				  heredoc.c token_utils.c token.c setup_path.c check_path.c create_path_list.c\
				  get_cmd_path.c pid.c signal.c signal_two.c define.c error.c free.c\
				  free_two.c free_three.c pipe.c path.c if_builtin.c if_command_valid.c\
				  if_double_operator.c if_expandable.c if_fork_needed.c if_grammar_valid.c\
				  if_identifier_valid.c if_in_quotes.c if_pipe_valid.c if_quotes_valid.c\
				  if_redir_valid.c if_redir.c if_token_valid.c if_no_meta.c

VPATH 			= $(SRCS_PATH):$(SRCS_PATH)builtins:$(SRCS_PATH)init:$(SRCS_PATH)cmd:\
				  $(SRCS_PATH)execution:$(SRCS_PATH)hash:$(SRCS_PATH)parsing:\
				  $(SRCS_PATH)signal:$(SRCS_PATH)path:$(SRCS_PATH)signals:$(SRCS_PATH)utils:\
				  $(SRCS_PATH)condition

OBJS			= $(addprefix $(OBJS_PATH), $(notdir $(SRCS:.c=.o)))

$(OBJS_PATH)%.o: %.c
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) $(CINC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(CINC) -o $(NAME) $(OBJS) -L $(LIBFT_PATH) -lft $(CREAD)
	@echo "$(NAME) is up to date."

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJS_PATH)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -rf $(NAME)

re: fclean all
	@echo "$(NAME) recompiled."

.PHONY: all clean fclean re
