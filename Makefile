NAME = cub3D
INCL = ./include/
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX = minilibx_macos
LIBFT_DIR = libft/
LIBFT = libftprintf.a
MLX_FLAGS = -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
MLX_FLAGS = -L$(MLX) -lmlx -framework OpenGL -framework AppKit

SRC_DIR = src/
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR), main.c \
	parsing.c parsing_utils.c file_saver.c \
	check_texture_data.c check_valid_color.c check_valid_map.c \
	get_next_line_cub.c get_next_line_cub_utils.c handle_errors.c \
	map_utils.c map.c map_utils2.c \
	render.c render_utils.c draw.c hooks.c )

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

$(NAME): $(LIBFT) $(OBJ) $(OBJ_DIR)
	$(CC)  -L $(MLX) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL) -I $(MLX) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	mv $(addprefix $(LIBFT_DIR), $(LIBFT)) .

linux: $(LIBFT) $(OBJ) $(OBJ_DIR)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
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
	norminette $(addprefix $(PRINTF_DIR), *.c) $(addprefix $(PRINTF_DIR), *.h) -R CheckDefine
	norminette $(addprefix $(LIBFT_DIR), *.c) $(addprefix $(LIBFT_DIR), *.h) -R CheckDefine

.phony: re clean fclean all norm

# NAME = cub3d
# INCL = ./include/
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g
# MLX = minilibx_macos
# LIBFT_DIR = libft/
# LIBFT = libftprintf.a
# MLX_FLAGS = $(shell pkg-config --cflags --libs $(MLX))

# SRC_DIR = src/
# OBJ_DIR = obj

# SRC = $(addprefix $(SRC_DIR), main.c parsing.c parsing_utils.c file_saver.c check_texture_data.c check_valid_color.c check_valid_map.c get_next_line_cub.c get_next_line_cub_utils.c handle_errors.c map_utils.c map.c map_utils2.c render.c render_utils.c)
# OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# $(NAME): $(LIBFT) $(OBJ) $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# all: $(NAME)

# $(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
# 	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

# $(OBJ_DIR):
# 	mkdir -p $@

# $(LIBFT):
# 	make -C $(LIBFT_DIR)
# 	cp $(addprefix $(LIBFT_DIR), $(LIBFT)) .

# linux: $(LIBFT) $(OBJ) $(OBJ_DIR)
# 	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

# clean:
# 	make -C $(LIBFT_DIR) clean
# 	rm -f $(LIBFT)
# 	rm -rf $(OBJ_DIR)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# mac:
# 	arch -x86_64 make

# macre: fclean mac

# norm:
# 	norminette $(addprefix $(SRC_DIR), *.c) -R CheckDefine
# 	norminette $(addprefix $(PRINTF_DIR), *.c) $(addprefix $(PRINTF_DIR), *.h) -R CheckDefine
# 	norminette $(addprefix $(LIBFT_DIR), *.c) $(addprefix $(LIBFT_DIR), *.h) -R CheckDefine

# .PHONY: re clean fclean all norm

# NAME = cub3d
# INCL = ./include/
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g
# MLX = minilibx_macos
# LIBFT_DIR = libft/
# LIBFT = libftprintf.a
# MLX_FLAGS = -L$(MLX) -lmlx -framework OpenGL -framework AppKit

# SRC_DIR = src/
# OBJ_DIR = obj

# SRC = $(addprefix $(SRC_DIR), main.c parsing.c parsing_utils.c file_saver.c check_texture_data.c check_valid_color.c check_valid_map.c get_next_line_cub.c get_next_line_cub_utils.c handle_errors.c map_utils.c map.c map_utils2.c render.c render_utils.c)
# OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ) | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# $(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
# 	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

# $(OBJ_DIR):
# 	mkdir -p $@

# $(LIBFT):
# 	make -C $(LIBFT_DIR)
# 	cp $(addprefix $(LIBFT_DIR), $(LIBFT)) .

# clean:
# 	make -C $(LIBFT_DIR) clean
# 	rm -f $(LIBFT)
# 	rm -rf $(OBJ_DIR)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# norm:
# 	norminette $(SRC_DIR)*.c
# 	norminette $(LIBFT_DIR)*.c $(LIBFT_DIR)*.h

# .PHONY: all clean fclean re norm

# NAME = cub3d
# INCL = ./include/
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

# MLX = minilibx_macos
# LIBFT_DIR = libft/
# LIBFT = libftprintf.a
# MLX_FLAGS = -L$(MLX) -lmlx -framework OpenGL -framework AppKit

# SRC_DIR = src/
# OBJ_DIR = obj

# SRC = $(addprefix $(SRC_DIR), main.c parsing.c parsing_utils.c file_saver.c check_texture_data.c check_valid_color.c check_valid_map.c get_next_line_cub.c get_next_line_cub_utils.c handle_errors.c map_utils.c map.c map_utils2.c render.c render_utils.c)
# OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# $(NAME): $(LIBFT) $(OBJ) | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -L$(MLX) $(MLX_FLAGS) -o $(NAME)

# all: $(NAME)

# $(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
# 	$(CC) -c $(CFLAGS) -I$(INCL) -I$(MLX) $< -o $@

# $(OBJ_DIR):
# 	mkdir -p $@

# $(LIBFT):
# 	make -C $(LIBFT_DIR)
# 	cp $(addprefix $(LIBFT_DIR), $(LIBFT)) .

# linux: $(LIBFT) $(OBJ) $(OBJ_DIR)
# 	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

# clean:
# 	make -C $(LIBFT_DIR) clean
# 	rm -f $(LIBFT)
# 	rm -rf $(OBJ_DIR)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# mac:
# 	arch -x86_64 make

# macre: fclean mac

# norm:
# 	norminette $(addprefix $(SRC_DIR), *.c) -R CheckDefine
# 	norminette $(addprefix $(PRINTF_DIR), *.c) $(addprefix $(PRINTF_DIR), *.h) -R CheckDefine
# 	norminette $(addprefix $(LIBFT_DIR), *.c) $(addprefix $(LIBFT_DIR), *.h) -R CheckDefine

# .PHONY: re clean fclean all norm
