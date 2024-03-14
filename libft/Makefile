# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melsahha <melsahha@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 16:28:04 by melsahha          #+#    #+#              #
#    Updated: 2024/03/14 10:22:45 by melsahha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
INCL = ./include/
CC= cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a
LIBFT_DIR = ./libft_src/

SRC_DIR = printf_src/
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR), ft_printf.c ft_putuint.c ft_putnbr.c ft_putchar.c ft_puthex.c ft_putpoint.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))


$(NAME): $(OBJS) $(OBJ_DIR)
	make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)$(LIBFT) .
	mv $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(LIBFT)
	make -sC $(LIBFT_DIR) clean


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
