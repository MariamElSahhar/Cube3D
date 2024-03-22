/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:15:18 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/22 13:22:31 by marmoham         ###   ########.fr       */
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
	while (y_m < (y + mlx->game.mini_tile))
	{
		while (x_m < (x + mlx->game.mini_tile))
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

	r = mlx->game.mini_tile / 3;
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

void	draw_tiny_map2(t_cub *mlx)
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
		while (mlx->game.map.map_2d[y][x]
			&& mlx->game.map.map_2d[y][x] != '\n')
		{
			if (mlx->game.map.map_2d[y][x] == '1')
				draw_small_win(mlx, x_p, y_p, 0x808080);
			else
				draw_small_win(mlx, x_p, y_p, 0xFFFFFF);
			x++;
			x_p += mlx->game.mini_tile;
		}
		y++;
		y_p += mlx->game.mini_tile;
	}
}

void	draw_tiny_map(t_cub *mlx)
{
	draw_tiny_map2(mlx);
	draw_player_pos(mlx, mlx->player.pos[0] / TILE * mlx->game.mini_tile,
		mlx->player.pos[1] / TILE * mlx->game.mini_tile, 0xFF9300FF);
}
