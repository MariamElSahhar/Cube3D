/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:37:09 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/09 20:19:27 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


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

# define ROT 45 * (M_PI / 180)
# define FOV 60 * (M_PI / 180)
# define SPEED 5
# define TILE 25

typedef struct s_map {
	int		floor[3];
	int		ceiling[3];
	int		**map;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		dir;
	int		pos[2];
} t_map;

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_mlx;

#endif
