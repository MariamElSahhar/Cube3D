/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:44:14 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 22:09:46 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= DIM_W || x < 0 || y >= DIM_H || y < 0)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	get_angle(char dir)
{
	float	angle;

	if (dir == 'N')
		angle = M_PI / 2;
	if (dir == 'S')
		angle = - M_PI / 2;
	if (dir == 'E')
		angle = 0;
	if (dir == 'W')
		angle = M_PI;
	return (angle);
}

/* void	cast_ray(int x, t_map *map, t_mlx *mlx) {
	(void) map;
	for (int i = 0; i < DIM_H; i++) {
		put_pixel(mlx->mlx, x, i, 0x331133);
	}
} */

/* void	put_map(t_map *map, t_player *player, t_mlx *mlx)
{
	float	start_angle;
	float	end_angle;
	int		x;
	float	angle_increment;

	(void) map;
	(void) mlx;
	player->alpha = get_angle(map->dir);
	printf("player facing %f\n", player->alpha);
	angle_increment = FOV / DIM_W;
	start_angle = player->alpha - ((FOV / 2) * (M_PI / 180));
	end_angle = player->alpha + ((FOV / 2) * (M_PI / 180));
	x = 0;
	while (x < DIM_W)
	{
		cast_ray(x, map, mlx);
		x += angle_increment;
	}
} */
