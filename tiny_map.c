/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:15:18 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/18 12:56:05 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= DIM_W)
		return ;
	if (y < 0)
		return ;
	else if (y >= DIM_H)
		return ;
	put_pixel(mlx, x, y, color);
}

static void	draw_small_win(t_cub *mlx, int x, int y, int color)
{
	int		x_m;
	int		y_m;

	y_m = y;
	x_m = x;
	while (y_m < (y + TILE_SIZE_R))
	{
		while (x_m < (x + TILE_SIZE_R))
			my_mlx_pixel_put(&mlx->mlx, x_m++, y_m, color);
		y_m++;
		x_m = x;
	}
}

static void	draw_player_pos(t_cub *mlx, int x_p, int y_p, int color)
{
	int		x;
	int		y;
	int		r;

	r = TILE_SIZE_R / 3;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (pow(x, 2) + pow(y, 2) <= pow(r, 2))
				my_mlx_pixel_put(&mlx->mlx, x_p + x, y_p + y, color);
			x++;
		}
		y++;
	}
}

void	draw_tiny_map(t_cub *mlx)
{
	int		y;
	int		x;
	int		x_p;
	int		y_p;

	y = 0;
	y_p = 0;
	while (y < mlx->game.map.nline)
	{
		x = 0;
		x_p = 0;
		while (mlx->game.map.map_2d[y][x])
		{
			if (mlx->game.map.map_2d[y][x] == '1')
				draw_small_win(mlx, x_p, y_p, 0x808080);
			else
				draw_small_win(mlx, x_p, y_p, 0xFFFFFF);
			x++;
			x_p += TILE_SIZE_R;
		}
		y++;
		y_p += TILE_SIZE_R;
	}
	draw_player_pos(mlx, mlx->player.pos[0] / TILE * TILE_SIZE_R, mlx->player.pos[1] / TILE * TILE_SIZE_R, 0xFF9300FF);
}