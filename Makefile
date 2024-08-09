NAME = minishell

CC = gcc

# # Compiler flags
# CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = parsing.c j.c utils.c states.c

# Object files (corresponding .o files for each .c file)
OBJS = $(SRCS:.c=.o)

# Executable name

# Default target
all: $(NAME)

# Link object files to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile .c files to .o files
%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS) 

# Clean everything, including .o files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

# Phony targets (not actual files)
.PHONY: all clean fclean re
