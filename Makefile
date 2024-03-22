NAME = cub3D
INCL = ./include/
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX = minilibx_macos
LIB_MLX = libmlx.a
LIBFT_DIR = libft/
LIBFT = libftprintf.a
MLX_FLAGS = -L$(MLX) -lmlx -framework OpenGL -framework AppKit

SRC_DIR = src/
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR), main.c \
	parsing.c parsing_utils.c file_saver.c \
	check_texture_data.c check_valid_color.c check_valid_map.c \
	get_next_line_cub.c get_next_line_cub_utils.c handle_errors.c \
	map_utils.c map.c map_utils2.c \
	render.c render_utils.c draw.c hooks.c \
	tiny_map.c utils.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

$(NAME): $(LIBFT) $(OBJ) $(OBJ_DIR) $(LIB_MLX)
	$(CC)  -L $(MLX) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL) -I $(MLX) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIB_MLX):
	make -C $(MLX)/

$(LIBFT):
	make -C $(LIBFT_DIR)
	mv $(addprefix $(LIBFT_DIR), $(LIBFT)) .

linux: $(LIBFT) $(OBJ) $(OBJ_DIR)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX)/ clean
	rm -f $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

mac:
	arch -x86_64 make

macre: fclean mac

norm:
	norminette $(addprefix $(SRC_DIR), *.c) -R CheckDefine
	norminette include/cub3d.h include/ft_printf.h include/libft.h -R CheckDefine
	norminette $(addprefix $(LIBFT_DIR)libft_src/, *.c) $(addprefix $(LIBFT_DIR)include/, *.h) -R CheckDefine
	norminette $(addprefix $(LIBFT_DIR)printf_src/, *.c)

.phony: re clean fclean all norm
