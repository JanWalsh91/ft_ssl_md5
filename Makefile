# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 15:59:40 by jwalsh            #+#    #+#              #
#    Updated: 2018/08/07 09:44:25 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CXX = gcc
CFLAGS = -Wall -Werror -Wextra

# Sources #

SRCS = main.c
	
SRCS_HELPER_FUNCTIONS = ft_bytetohex.c \
	ft_bzero.c \
	ft_islower.c \
	ft_memalloc.c \
	ft_memcpy.c \
	ft_memset.c \
	ft_putchar.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_strcat.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strlen.c \
	ft_strtoupper.c \
	ft_toupper.c \
	hex_dump.c

SRCS_CORE = bitwise_operations.c \
	handle_arguments.c \
	print_messages.c \
	print_task_result.c \
	task_manager.c

SRCS_MD5 = ft_md5_helper_functions.c \
	ft_md5_test_suite.c \
	ft_md5_update_state.c \
	ft_md5.c

SRCS_SHA256 = ft_sha256_test_suite.c \
	ft_sha256_update_state.c \
	ft_sha256.c 

SRCS_SHA512 = ft_sha512_test_suite.c \
	ft_sha512_update_state.c \
	ft_sha512.c 

HEADER_DIR = ./inc
SRCS_DIR := ./src
OBJS_DIR := ./obj

HEADER_CORE = ft_ssl_core.h
HEADER_HELPER_FUNCTIONS = ft_ssl_helper_functions.h
HEADER_MD5 = ft_md5.h
HEADER_SHA256 = ft_sha256.h
HEADER_SHA512 = ft_sha512.h

OBJS := $(SRCS:.c=.o)
OBJS_CORE := $(SRCS_CORE:.c=.o)
OBJS_HELPER_FUNCTIONS := $(SRCS_HELPER_FUNCTIONS:.c=.o)
OBJS_MD5 := $(SRCS_MD5:.c=.o)
OBJS_SHA256 := $(SRCS_SHA256:.c=.o)
OBJS_SHA512 := $(SRCS_SHA512:.c=.o)

SRCS_CORE_DIR := core
SRCS_HELPER_FUNCTIONS_DIR := helper_functions
SRCS_MD5_DIR := md5
SRCS_SHA256_DIR := sha256
SRCS_SHA512_DIR := sha512

HEADER_CORE := $(addprefix $(HEADER_DIR)/, $(HEADER_CORE))
HEADER_HELPER_FUNCTIONS := $(addprefix $(HEADER_DIR)/, $(HEADER_HELPER_FUNCTIONS))
HEADER_MD5 := $(addprefix $(HEADER_DIR)/, $(HEADER_MD5))
HEADER_SHA256 := $(addprefix $(HEADER_DIR)/, $(HEADER_SHA256))
HEADER_SHA512 := $(addprefix $(HEADER_DIR)/, $(HEADER_SHA512))

OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
OBJS_CORE := $(addprefix $(OBJS_DIR)/, $(OBJS_CORE))
OBJS_HELPER_FUNCTIONS := $(addprefix $(OBJS_DIR)/, $(OBJS_HELPER_FUNCTIONS))
OBJS_MD5 := $(addprefix $(OBJS_DIR)/, $(OBJS_MD5))
OBJS_SHA256 := $(addprefix $(OBJS_DIR)/, $(OBJS_SHA256))
OBJS_SHA512 := $(addprefix $(OBJS_DIR)/, $(OBJS_SHA512))

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
SRCS_HELPER_FUNCTIONS := $(addprefix $(SRCS_HELPER_FUNCTIONS_DIR)/, $(SRCS_HELPER_FUNCTIONS))
SRCS_HELPER_FUNCTIONS := $(addprefix $(SRCS_DIR)/, $(SRCS_HELPER_FUNCTIONS))
SRCS_CORE := $(addprefix $(SRCS_CORE_DIR)/, $(SRCS_CORE))
SRCS_CORE := $(addprefix $(SRCS_DIR)/, $(SRCS_CORE))
SRC_MD5 := $(addprefix $(SRC_MD5_DIR)/, $(SRC_MD5))
SRC_MD5 := $(addprefix $(SRCS_DIR)/, $(SRC_MD5))
SRC_SHA256 := $(addprefix $(SRC_SHA256_DIR)/, $(SRC_SHA256))
SRC_SHA256 := $(addprefix $(SRCS_DIR)/, $(SRC_SHA256))
SRC_SHA512 := $(addprefix $(SRC_SHA512_DIR)/, $(SRC_SHA512))
SRC_SHA512 := $(addprefix $(SRCS_DIR)/, $(SRC_SHA512))

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

$(NAME): $(OBJS) $(OBJS_HELPER_FUNCTIONS) $(OBJS_CORE) $(OBJS_MD5) $(OBJS_SHA256) $(OBJS_SHA512)
	@$(CXX) $(CFLAGS) -o $@ $^
	@echo "$(C_CYAN)$(NAME) compiled$(C_NONE)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_CORE) $(HEADER_HELPER_FUNCTIONS)
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

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(SRCS_MD5_DIR)/%.c $(HEADER_MD5)
	@echo "$(C_CYAN)Compiling $<$(C_NONE)"
	@/bin/mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADER_DIR) -c -o $@ $<

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(SRCS_SHA256_DIR)/%.c $(HEADER_SHA256)
	@echo "$(C_CYAN)Compiling $<$(C_NONE)"
	@/bin/mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HEADER_DIR) -c -o $@ $<

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(SRCS_SHA512_DIR)/%.c $(HEADER_SHA512)
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
