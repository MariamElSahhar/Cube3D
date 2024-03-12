/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:43 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/12 20:11:11 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_mlx(t_cub *data)
{
	printf("mlx init\n");
	data->mlx.mlx = mlx_init();
	printf("mlx new image\n");
	data->mlx.img = mlx_new_image(data->mlx.mlx, DIM_W, DIM_H);
	printf("mlx get data addr\n");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&(data->mlx.bits_per_pixel), &(data->mlx.line_length),
			&(data->mlx.endian));
	printf("mlx new window\n");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			DIM_W, DIM_H, "Hello World");
	data->player.pos[0] = (data->game.map.player_x * TILE) + (TILE / 2);
	data->player.pos[1] = (data->game.map.player_y * TILE) + (TILE / 2);
	data->player.alpha = cardinal_to_angle(data->game.map.player_dir);
	printf("done data init\n");
	return (1);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= DIM_W || x < 0 || y >= DIM_H || y < 0)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_texture(t_cub *data, double x, int y, char d)
{
}

void	render_wall(double x, double dist, t_cub *data, char dir)
{
	int		y;
	double	wall;
	double	top;
	double	bottom;

	y = 0;
	wall_height(dist, &wall, &top, &bottom);
	while (y < top)
		put_pixel(&data->mlx, x, y++, data->game.ceiling);
	while (y < top + wall)
	{
		put_texture(data, x, y, dir);
		if (dir == 'N' || dir == 'S')
			put_pixel(&data->mlx, x, y++, 0xFFC300); // green
		else
			put_pixel(&data->mlx, x, y++, 0xDAF7A6); // yellow
	}
	while (y < DIM_H)
		put_pixel(&data->mlx, x, y++, data->game.floor);
}
