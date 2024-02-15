/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:37:09 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 20:32:48 by melsahha         ###   ########.fr       */
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

# define NORTH 1
# define SOUTH 2
# define WEST 3
# define EAST 4

# define DIM_W 1200
# define DIM_H 1000

# define ROT 45
# define FOV 60
# define SPEED 5
# define TILE 25

typedef struct s_map {
	int		floor[3];
	int		ceiling[3];
	int		**grid;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		dir;
	int		pos[2];
	size_t	rows;
	size_t	cols;
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

int		parse_map(char *filename, t_map *map);
int		read_map(t_map *map, int fd);
int		rows_cols(t_map *map, int fd, char *line);
int		parse_grid(t_map *map, char *filename, int i);

int		read_texture(t_map *map, char *dir, char *data);
int		read_f_c(t_map *map, char type, char *data);

int		map_data_complete(t_map *map);
char	*skip_empty_lines(int fd, char *line, int *i);
void	free_double_pointer_size(void **ptr, int size);
void	free_double_pointer(void **ptr);
void	print_grid(t_map *map);
int		str_isdigits(char *str);

void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	put_map(t_data *data);

#endif
