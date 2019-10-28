# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 15:50:40 by vkuksa            #+#    #+#              #
#    Updated: 2019/10/28 15:50:43 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = clp.a

CFILES = clp.c clp_cmd_getters.c clp_flag_getters.c clp_print_usage.c \
clp_clear.c clp_creation_utils.c clp_parse.c clp_utils.c

INCFILES = clp.h clp_data_types.h clp_internal.h

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

LFT_DIR = ../libft
LFT_INC_DIR = $(LFT_DIR)/includes
LFT_LIB = $(LFT_DIR)/libft.a

SRC = $(addprefix $(SRC_DIR)/, $(CFILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))
INC = $(addprefix $(INC_DIR)/, $(INCFILES))

CC = clang
FLAGS = -Wall -Werror -Wextra

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

SP1 = 10
SP2 = 35

all: $(NAME)

$(NAME): $(LFT_LIB) $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(LFT_LIB):
	@make -C $(LFT_DIR)
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR):
	@mkdir $@
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c -I $(INC_DIR) -I $(LFT_INC_DIR) $(FLAGS) $< -o $@
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@printf "%-$(SP1)s%-$(SP2)s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@/bin/rm -rf $(NAME)
	@printf "%-$(SP1)s%-$(SP2)s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean $(NAME)

norm:
	norminette $(SRC_DIR) $(INC_DIR)
