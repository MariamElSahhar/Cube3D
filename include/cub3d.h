/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:37:09 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/22 20:24:28 by melsahha         ###   ########.fr       */
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

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4
# define DIRECTION "NSEW"

# define DIM_W 1200
# define DIM_H 1000

# define ROT 45
# define FOV 60
# define SPEED 5
# define TILE 25

// typedef struct s_map {
// 	int		**grid;
// 	int		floor[3];
// 	int		ceiling[3];
// 	char	*north;
// 	char	*south;
// 	char	*east;
// 	char	*west;
// 	char	dir;
// 	int		pos[2];
// 	size_t	rows;
// 	size_t	cols;
// }	t_map;

typedef struct s_map
{
	char	**map;
	char	**texture;
	char	orientation;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		*floor;
	int		*ceiling;
	int		time;
}	t_map;

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_player {
	int		pos[2];
	float	alpha;
}	t_player;

typedef struct s_data {
	t_mlx		mlx;
	t_map		map;
	t_player	player;
}	t_data;

// int		parse_map(char *filename, t_map *map);
/* int		read_map(t_map *map, int fd);
int		rows_cols(t_map *map, int fd, char *line);
int		parse_grid(t_map *map, char *filename, int i);

int		read_texture(t_map *map, char *dir, char *data);
int		read_f_c(t_map *map, char type, char *data);

int		map_data_complete(t_map *map);
char	*skip_empty_lines(int fd, char *line, int *i);
 */


bool	check_cubfile_extention(char *file);
int	count_map_size(char **tab);
char	**get_content_2darray(char *file, int fd, char **line);
bool	parsing_main_map(char **argv, t_map *map_info);
int	count_map_size(char **tab);
char	*ft_trim_string(char *str, char c);
int		check_valid_file(int fd);
int		read_nbline_file(int fd);
int		count_nbline_file(char *file);
int		determine_line_type(char *str);
bool	check_valid_tile(char c);
char	*ft_fill_map(int len, char c);
int		check_valid_mapline(char *str, int i, int start);
bool	is_valid_content(char **value);
char	*copy_line_dup(const char *str, size_t len);
int		get_mapwidth(char **map, int i, int depth);
bool	loop_check_row(t_map *map_data, int i, int j);
bool	check_wall_hor(t_map *map_data, int i, int nb_col, int j);
bool	loop_check_colume(t_map *map_data, int i, int j);
bool	check_wall_vert(t_map *map_info, int i, int nb_row, int j);
bool	check_closed_map(t_map *map_data, int i, int j);
bool	find_playerpos(t_map *map_data, int i, int j, bool pos);
bool	loop_parse_map(char **content, t_map *map_data, int i);
int		check_map_order_char(char **array, int start);
int		get_map_end(char **array, int start, int j, t_map *map_data);
bool	parsing_valid_map_data(char **array, t_map *map_data);
bool	is_valid_cube_colorline(char *str);
bool	color_cube_loop(char **numbers, int *color);
bool	valid_color_parsing(char **content, t_map *map_info, char type);
bool	find_texture_pos(char **array, char *ori, char **texture, int x);
bool	is_texture_file_xpm(char *string);
bool	check_texture_file(char **texture);
bool	texture_parsing(char **array, t_map *map_data);
void	ft_free_array(char **tab);
bool	free_color(char **color);
bool	print_msg(char *msg, int fd);
void	free_map(t_map *map_data);
int		get_next_line_cub(int fd, char **line);
void	gnl_free(char **save);

void	free_double_pointer_size(void **ptr, int size);
void	free_double_pointer(void **ptr);
void	print_grid(t_map *map);
int		str_isdigits(char *str);

void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	put_map(t_data * data, t_map *map, t_player *player);
float	normalize_angle(float angle);
float	cardinal_to_angle(char dir);
int		hit_wall(float x, float y, t_map *map);

#endif
