/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:50:54 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 16:19:18 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../../include/libft.h"
//# include "mlx/mlx.h"
//# include "mlx.h"

# define DIRECTION "NSEW"
# define SCREEN_WIDTH 1900
# define SCREAN_HIGHT 1000
# define TILE_SIZE 32
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_MOVE_SPEED 4


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
	int		*ceilling;
	int		time;
}	t_map;

bool	check_cubfile_extention(char *file);
int	count_map_size(char **tab);
char	**get_content_2darray(char *file, int fd, char **line);
bool	parsing_main_map(char **argv, t_map *map_info);
int	count_map_size(char **tab);
char	*ft_trim_string(char *str, char c);
int	check_valid_file(int fd);
int	read_nbline_file(int fd);
int	count_nbline_file(char *file);
int	determine_line_type(char *str);
bool	check_valid_tile(char c);
char	*ft_fill_map(int len, char c);
int	check_valid_mapline(char *str, int i, int start);
bool	is_valid_content(char **value);
char	*copy_line_dup(const char *str, size_t len);
int	get_mapwidth(char **map, int i, int depth);
bool	loop_check_row(t_map *map_data, int i, int j);
bool	check_wall_hor(t_map *map_data, int i, int nb_col, int j);
bool	loop_check_colume(t_map *map_data, int i, int j);
bool	check_wall_vert(t_map *map_info, int i, int nb_row, int j);
bool	check_closed_map(t_map *map_data, int i, int j);
bool	find_playerpos(t_map *map_data, int i, int j, bool pos);
bool	loop_parse_map(char **content, t_map *map_data, int i);
int	check_map_order_char(char **array, int start);
int	get_map_end(char **array, int start, int j, t_map *map_data);
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

#endif
