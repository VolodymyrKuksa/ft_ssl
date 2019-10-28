# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 16:04:14 by vkuksa            #+#    #+#              #
#    Updated: 2019/10/28 16:04:16 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

MD5_DIR = md5
SHA256_DIR = sha256

CFILES = main.c $(MD5_DIR)/md5.c $(MD5_DIR)/md5_round_functions.c padding.c \
common.c $(MD5_DIR)/md5_g_functions.c $(MD5_DIR)/md5_constants.c \
$(SHA256_DIR)/sha256.c $(SHA256_DIR)/sha256_constants.c endianness_utils.c \
execute_hash_function.c io.c clp_functions.c

INCFILES = data_types.h ft_ssl.h md5.h sha256.h

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/

LFT_DIR = libft
LFT_INC_DIR = $(LFT_DIR)/includes
LFT_LIB = $(LFT_DIR)/libft.a

CLP_DIR = command_line_parser
CLP_INC_DIR = $(CLP_DIR)/includes
CLP_LIB = $(CLP_DIR)/clp.a

SRC = $(addprefix $(SRC_DIR), $(CFILES))
OBJ = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
INC = $(addprefix $(INC_DIR), $(INCFILES))

CC = clang
FLAGS = -Wall -Werror -Wextra

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

SP1 = 10
SP2 = 35

all: $(NAME)

$(NAME): $(LFT_LIB) $(CLP_LIB) $(OBJ_DIR) $(OBJ_DIR)/$(MD5_DIR) \
	$(OBJ_DIR)/$(SHA256_DIR) $(OBJ)
	@$(CC) $(OBJ) $(LFT_LIB) $(CLP_LIB) -o $(NAME)
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(LFT_LIB):
	@make -C $(LFT_DIR)
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(CLP_LIB):
	@make -C $(CLP_DIR)
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR):
	@mkdir $@
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR)/$(MD5_DIR):
	@mkdir $@
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR)/$(SHA256_DIR):
	@mkdir $@
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC)
	@$(CC) -c -I $(INC_DIR) -I $(LFT_INC_DIR) -I $(CLP_INC_DIR) $(FLAGS) \
	$< -o $@
	@printf "%-$(SP1)s%-$(SP2)s$(C_GREEN)[done]$(C_NONE)\n" $(NAME): $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LFT_DIR) clean
	@make -C $(CLP_DIR) clean
	@printf "%-$(SP1)s%-$(SP2)s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LFT_DIR) fclean
	@make -C $(CLP_DIR) fclean
	@printf "%-$(SP1)s%-$(SP2)s$(C_RED)[done]$(C_NONE)\n" $(NAME): $@

re: fclean $(NAME)

norm:
	@make -C $(LFT_DIR) norm
	@make -C $(CLP_DIR) norm
	norminette $(SRC_DIR) $(INC_DIR)

test:
	@printf "\n%s: $(C_GREEN)[MD5]$(C_NONE)\n" $@
	@sh test_md5.sh
	@printf "\n%s: $(C_GREEN)[SHA256]$(C_NONE)\n" $@
	@sh test_sha256.sh
