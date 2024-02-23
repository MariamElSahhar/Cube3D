/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:44:14 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/23 17:28:00 by melsahha         ###   ########.fr       */
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


double	h_intersect_dist(double alpha, t_map *map, t_player *player)
{
	double	x_incr, y_incr;
	double	x_first, y_first;

	printf("getting horizontal line intersect\n");
	y_incr = TILE;
	x_incr = TILE / tan(alpha);
	if (fabs(x_incr) >= (map->map_width * 25))
		return (FLT_MAX);
	y_first = player->pos[1] - (player->pos[1] % TILE);
	x_first = ((player->pos[1] - y_first) / tan(alpha)) + player->pos[0];
	double	i = 0;
	while (floor((x_first + (x_incr * i)) / TILE) > 0
		&& floor((x_first + (x_incr * i)) / TILE) < map->map_width
		&& floor((y_first + (y_incr * i)) / 25) > 0
		&& floor((y_first + (y_incr * i)) / 25) < map->map_height)
	{
		if(hit_wall(x_first + (x_incr * i), y_first + (y_incr * i), map))
			return (sqrt(pow(x_first + x_incr * i, 2) + pow(y_first + y_incr * i, 2)));
		i++;
	}
	printf("horizontal intersect at %f, %f\n", x_first + x_incr * i, y_first + y_incr * i);
	return (sqrt(pow(x_first + x_incr * i, 2) + pow(y_first + y_incr * i, 2)));
}

double	v_intersect_dist(double alpha, t_map *map, t_player *player)
{
	double	x_incr, y_incr;
	double	x_first, y_first;

	printf("getting vertical line intersect\n");
	x_incr = TILE;
	y_incr = TILE * tan(alpha);
	if (fabs(y_incr) >= (map->map_height * 25))
		return (FLT_MAX);
	x_first = player->pos[0] - (player->pos[0] % TILE);
	y_first = ((player->pos[0] - x_first) * tan(alpha)) + player->pos[1];
	printf("x_inc = %f, y_inc = %f, starting at (%f, %f)\n", x_incr, y_incr, x_first, y_first);
	int	i = 0;
	while (floor((x_first + (x_incr * i)) / TILE) > 0
		&& floor((x_first + (x_incr * i)) / TILE) < map->map_width
		&& floor((y_first + (y_incr * i)) / 25) > 0
		&& floor((y_first + (y_incr * i)) / 25) < map->map_height)
	{
		if(hit_wall(x_first + (x_incr * i), y_first + (y_incr * i), map))
			return (sqrt(pow(x_first + x_incr * i, 2) + pow(y_first + y_incr * i, 2)));
		i++;
	}
	printf("vertical intersect at %f, %f\n", x_first + x_incr * i, y_first + y_incr * i);
	return (FLT_MAX);
}

// void	render_wall(double alpha, int dist, t_map *map)
// {

// }

double	distance_to_wall(double alpha, t_map *map, t_player *player)
{
	double	v_dist;
	double	h_dist;
	double	dist;

	printf("getting distance to nearest wall alpha = %d\n", alpha == 0.0);
	v_dist = h_intersect_dist(alpha, map, player);
	h_dist = v_intersect_dist(alpha, map, player);
	if (v_dist < h_dist)
		dist = v_dist;
	else
		dist = h_dist;
	printf("distance to nearest wall is %f\n", dist);
	// render_wall(alpha, dist, map);
	return(dist);
}

void	cast_ray(int x, double alpha, t_data *data)
{
	double	dist;

	dist = distance_to_wall(alpha, &data->map, &data->player);
	printf("distance to nearest wall is %f\n", dist);
	for (int i = 0; i < DIM_H; i++) {
		put_pixel(&data->mlx, x, i, 0x4B0082);
	}
}


void	put_map(t_data *data, t_map *map, t_player *player)
{
	printf("----calculating distances-----\n");
	double	start_angle;
	double	end_angle;
	int		x;
	double	angle_increment;
	(void) data;

	player->alpha = cardinal_to_angle(map->orientation);
	printf("player facing %c => %f\n", map->orientation, player->alpha);
	angle_increment = ((double) FOV / (double) DIM_W ) * (M_PI / 180);
	start_angle = player->alpha - ((FOV / 2) * (M_PI / 180));
	end_angle = player->alpha + ((FOV / 2) * (M_PI / 180));
	printf("increment %f, %f to %f\n", angle_increment, start_angle* (180 / M_PI), end_angle* (180 / M_PI));
	x = 0;
	// x = DIM_W / 2;
	while (x < DIM_W)
	{
		printf("ray #%d, angle = %f\n", x, normalize_angle(start_angle + (angle_increment * x)) * (180 / M_PI));
		cast_ray(x, start_angle + (angle_increment * x), data);
		x ++;
	}
	printf("\n");
}
