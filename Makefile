# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 15:59:40 by jwalsh            #+#    #+#              #
#    Updated: 2018/07/25 14:55:39 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CXX = gcc
CFLAGS = -Wall -Werror -Wextra

# Sources #

SRCS = main.c \
	print_usage.c

SRCS_HELPER_FUNCTIONS = ft_putchar.c \
	ft_putstr.c \
	ft_strcmp.c \
	ft_strlen.c

SRCS_CORE = read.c

HEADER_DIR = ./inc
SRCS_DIR := ./src
OBJS_DIR := ./obj

HEADER = ft_ssl.h

HEADER_CORE = core.h
HEADER_HELPER_FUNCTIONS = helper_functions.h

OBJS := $(SRCS:.c=.o)
OBJS_CORE := $(SRCS_CORE:.c=.o)
OBJS_HELPER_FUNCTIONS := $(SRCS_HELPER_FUNCTIONS:.c=.o)

SRCS_CORE_DIR := core
SRCS_HELPER_FUNCTIONS_DIR := helper_functions

HEADER := $(addprefix $(HEADER_DIR)/, $(HEADER))

HEADER_CORE := $(addprefix $(HEADER_DIR)/, $(HEADER_CORE))
HEADER_HELPER_FUNCTIONS := $(addprefix $(HEADER_DIR)/, $(HEADER_HELPER_FUNCTIONS))

OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
OBJS_CORE := $(addprefix $(OBJS_DIR)/, $(OBJS_CORE))
OBJS_HELPER_FUNCTIONS := $(addprefix $(OBJS_DIR)/, $(OBJS_HELPER_FUNCTIONS))

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
SRCS_HELPER_FUNCTIONS := $(addprefix $(SRCS_HELPER_FUNCTIONS_DIR)/, $(SRCS_HELPER_FUNCTIONS))
SRCS_HELPER_FUNCTIONS := $(addprefix $(SRCS_DIR)/, $(SRCS_HELPER_FUNCTIONS))
SRCS_CORE := $(addprefix $(SRCS_CORE_DIR)/, $(SRCS_CORE))
SRCS_CORE := $(addprefix $(SRCS_DIR)/, $(SRCS_CORE))

test:
	@echo $(SRCS_CORE)
	@echo $(SRCS_DIR)/$(SRCS_CORE_DIR)/%.c
	@echo $(OBJS_DIR)/%.o

# Colors #

C_NONE = \033[0m
C_BOLD = \033[1m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_BROWN = \033[33m
C_BLUE = \033[34m
C_MAGENTA = \033[35m
C_CYAN = \033[36m
C_GRAY = \033[37m

# Rules #

opti:
	@$(MAKE) -j all

debug:
	@$(MAKE) all

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_HELPER_FUNCTIONS) $(OBJS_CORE)
	@$(CXX) $(CFLAGS) -o $@ $^
	@echo "$(C_CYAN)$(NAME) compiled$(C_NONE)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@echo "$(C_CYAN)Compiling $<$(C_NONE)"
	@/bin/mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADER_DIR) -c -o $@ $<

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(SRCS_HELPER_FUNCTIONS_DIR)/%.c $(HEADER_HELPER_FUNCTIONS)
	@echo "$(C_CYAN)Compiling $<$(C_NONE)"
	@/bin/mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADER_DIR) -c -o $@ $<

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(SRCS_CORE_DIR)/%.c $(HEADER_CORE)
	@echo "$(C_CYAN)Compiling $<$(C_NONE)"
	@/bin/mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADER_DIR) -c -o $@ $<

clean:
	@-/bin/rm -rf $(OBJS_DIR)
	@echo "$(C_CYAN)$(NAME) cleaned$(C_NONE)"

fclean: clean
	@-/bin/rm -f $(NAME)
	@echo "$(C_CYAN)$(NAME) fcleaned$(C_NONE)"

re: fclean opti

.PHONY: all clean fclean re
