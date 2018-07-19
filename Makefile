# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 15:59:40 by jwalsh            #+#    #+#              #
#    Updated: 2018/07/19 13:45:09 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CXX = gcc
CFLAGS = -Wall -Werror -Wextra

# Sources #

SRCS = main.c

HEADERS = ft_ssl.h
HEADER_DIR = inc/

OBJS := $(SRCS:.c=.o)
SRCS_DIR := ./src
OBJS_DIR := ./obj
HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

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

$(NAME): $(OBJS)
	@$(CXX) $(CFLAGS) -I$(HEADER_DIR) $< -o $@
	@echo "$(C_CYAN)$(NAME) compiled$(C_NONE)"

$(OBJS): $(SRCS) $(HEADERS)
	@$(CXX) -I$(HEADER_DIR) $(CFLAGS) -o $@ -c $< -g

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@-/bin/rm -rf $(OBJS_DIR)
	@echo "$(C_CYAN)$(NAME) cleaned$(C_NONE)"

fclean: clean
	@-/bin/rm -f $(NAME)
	@echo "$(C_CYAN)$(NAME) fcleaned$(C_NONE)"

re: fclean opti

.PHONY: all clean fclean re
