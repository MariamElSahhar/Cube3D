/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:37:09 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/11 21:32:35 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include <float.h>

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4
# define DIRECTION "NSEW"

# define DIM_W 1200
# define DIM_H 1000

# define ROT 8
# define FOV 60
# define SPEED 5
# define TILE 50.0000

typedef struct s_map
{
	int		nline;
	int		map_width;
	int		map_pos;
	char	**map_2d;
	char	*line;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_file
{
	int		fd;
	int		nline;
	char	*line;
	char	**file_2d;
}				t_file;

typedef struct s_game
{
	t_map	map;
	t_file	file;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;
}				t_game;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_player
{
	int		pos[2];
	float	alpha;
}	t_player;

typedef struct s_cub
{
	int		i;
	int		fd;
	int		j;
	char	*line;
	char	**tmp;
	int		*f_colors;
	int		*c_colors;
	t_mlx	mlx;
	t_game	game;
	t_player	player;
}	t_cub;

typedef enum e_keycodes
{
	ESC = 53,
	LEFT = 123,
	RIGHT = 124,
	DOWN = 125,
	UP = 126,
}	t_keycodes;

// typedef struct s_data {
// 	t_mlx		mlx;
// 	t_map		map;
// 	t_player	player;

// }	t_data;

void	ft_free_array(char **tab);
void	free_cube_map(t_cub *cub);
void	print_error(char *msg, t_cub *cub);
char	*new_strtrimchar(char const *str, int const c);
void	check_map_space(int y, int x, t_cub *cub);
void	check_map_edge(char *line, t_cub *map);
void	is_valid_char(int y, int c, t_cub *cub);
bool	check_is_player(int c);
void	check_is_space(int c, int y, int x, t_cub *cub);
char	*copy_and_trim(char *line);
bool	check_is_map_begininng(char *line);
char	**create_2darray_dup(char **array, int start, int nline);
int		get_map_len(char **arrays);
void	saving_validate_map(char *line, int index, t_cub *cub);
void	check_is_2_commas(char *line, t_cub *cub);
void	is_args_valide(char *av, t_cub *cub);
int		my_atoi(char *str);
void	check_missing(t_cub *cub);
void	check_file_extension(char **args, char *file, t_cub *cub);
void	saving_valide_textures(char *line, t_cub *cub);
void	is_valide_identifier(char *line, t_cub *cub);
void	parse_map_components(t_cub *cub);

bool	is_valide_id(char *iden, char *cmp, int len);
bool	is_whitespace(int c);
void	check_texture_file(char **args, char *path, t_cub *cub);
bool	is_duplicate(char *iden, t_cub *cub);
void	check_texture_arg(char **arg, t_cub *cub);
int		saving_clr_content(char *line, char *content, char **color, t_cub *cub);
int		create_rgb_color(int r, int g, int b);
int		check_color_args(char *line, t_cub *cub);
int		checking_color(char *line, char *iden, t_cub *cub);
void	saving_parsing_colors(char *line, t_cub *cub);
void	is_valid_zero(int c, int y, int x, t_cub *cub);
void	get_player_pos(int c, int y, int x, t_cub *cub);
void	check_map_line(int y, t_cub *cub);
void	check_map(t_cub *cub);
void	get_map_width(t_cub *cub);
char	**file_to_2d(char **pre, char *line, int nline, t_cub *map);
void	saving_map_file(t_cub *map);
void	init_map(t_cub *map_data);
char	*get_next_line_cube(int fd);
int		gnl_strlen(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(char *s1);

// RENDERING
int		check_map_wall(char *line);
double	normalize_angle(double angle);
double	cardinal_to_angle(char dir);
int		hit_wall(double x, double y, t_map *map);
void	put_map(t_cub *data, t_map *map, t_player *player);

#endif
