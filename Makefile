
NAME = cub3d
INCL = ./include/
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX = minilibx_macos
LIBFT_DIR = libft/
LIBFT = libftprintf.a

SRC_DIR = src/
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR), main.c)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

$(NAME): $(LIBFT) $(OBJ) $(OBJ_DIR)
	$(CC) -L $(MLX) -lmlx -framework OpenGL -framework AppKit $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL) -I $(MLX) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	mv $(addprefix $(LIBFT_DIR), $(LIBFT)) .

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette *.c *.h -R CheckDefine
	norminette $(addprefix $(PRINTF_DIR), *.c) $(addprefix $(PRINTF_DIR), *.h) -R CheckDefine
	norminette $(addprefix $(LIBFT_DIR), *.c) $(addprefix $(LIBFT_DIR), *.h) -R CheckDefine

.phony: re clean fclean all norm
