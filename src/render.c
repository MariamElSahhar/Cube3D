/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:44:14 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/22 20:08:47 by melsahha         ###   ########.fr       */
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

float	cardinal_to_angle(char dir)
{
	float	angle;

	angle = -1.0;
	if (dir == 'N')
		angle = M_PI / 2;
	else if (dir == 'S')
		angle = - M_PI / 2;
	else if (dir == 'E')
		angle = 0;
	else if (dir == 'W')
		angle = M_PI;
	return (angle);
}

int	hit_wall(int x, int y, t_map *map) {
	int	x_coor;
	int	y_coor;

	printf("hit wall\n");
	x_coor = (x - (x % TILE)) / TILE;
	y_coor = (y - (y % TILE)) / TILE;
	printf("checking map for intersection at %i, %i --> \n", x_coor, y_coor);
	if (map->map[y_coor][x_coor] == 1) {
		printf("wall here\n");
		return (1);
	}
	printf("no wall here\n");
	return (0);
}

int	h_intersect_dist(float alpha, t_map *map, t_player *player)
{
	int	x_incr, y_incr;
	int	x_first, y_first;

	printf("getting horizontal line intersect\n");
	y_incr = TILE;
	x_incr = TILE / tan(alpha);
	y_first = player->pos[1] - (player->pos[1] % TILE);
	x_first = ((player->pos[1] - y_first) / tan(alpha)) + player->pos[0];
	int	i = 0;
	while (!hit_wall(x_first + x_incr * i, y_first + y_incr * i, map))
		i++;
	printf("horizontal intersect at %i, %i\n", x_first + x_incr * i, y_first + y_incr * i);
	return (sqrt(pow(x_first + x_incr * i, 2) + pow(y_first + y_incr * i, 2)));
}

int	v_intersect_dist(float alpha, t_map *map, t_player *player)
{
	int	x_incr, y_incr;
	int	x_first, y_first;

	printf("getting vertical line intersect\n");
	y_incr = TILE * tan(alpha);
	x_incr = TILE;


	x_first = player->pos[0] - (player->pos[0] % TILE);
	y_first = ((player->pos[0] - x_first) * tan(alpha)) + player->pos[1];
	int	i = 0;
	while (!hit_wall(x_first + x_incr * i, y_first + y_incr * i, map))
		i++;
	printf("vertical intersect at %i, %i\n", x_first + x_incr * i, y_first + y_incr * i);
	return (sqrt(pow(x_first + x_incr * i, 2) + pow(y_first + y_incr * i, 2)));
}

// void	render_wall(float alpha, int dist, t_map *map)
// {

// }

int	distance_to_wall(float alpha, t_map *map, t_player *player)
{
	float	v_dist;
	float	h_dist;
	float	dist;

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

void	cast_ray(int x, float alpha, t_data *data)
{
	int	dist;

	printf("getting distance to nearest wall\n");
	dist = distance_to_wall(alpha, &data->map, &data->player);
	printf("distance to nearest wall is %i\n", dist);
	for (int i = 0; i < DIM_H; i++) {
		put_pixel(&data->mlx, x, i, 0x4B0082);
	}
}

float	normalize_angle(float angle)
{
	float norm = fmod(angle, 2 * M_PI);

	if (norm < 0)
	{
		norm += 2 * M_PI;
	}
	return norm;
}

void	put_map(t_data *data, t_map *map, t_player *player)
{
	printf("----calculating distances-----\n");
	float	start_angle;
	float	end_angle;
	int		x;
	float	angle_increment;
	(void) data;

	player->alpha = cardinal_to_angle(map->orientation);
	printf("player facing %c => %f\n", map->orientation, player->alpha);
	angle_increment = ((float) FOV / (float) DIM_W ) * (M_PI / 180);
	start_angle = player->alpha - ((FOV / 2) * (M_PI / 180));
	end_angle = player->alpha + ((FOV / 2) * (M_PI / 180));
	printf("increment %f, %f to %f\n", angle_increment, start_angle* (180 / M_PI), end_angle* (180 / M_PI));
	x = 0;
	while (x < DIM_W)
	{
		// printf("ray #%d, angle = %f\n", x, normalize_angle(start_angle + (angle_increment * x)) * (180 / M_PI));
		printf("casting %i\n", x);
		cast_ray(x, start_angle + (angle_increment * x), data);
		x ++;
	}
	printf("\n");
}
