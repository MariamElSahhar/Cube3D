/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:44:14 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/26 20:35:44 by melsahha         ###   ########.fr       */
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
	double	x_incr;
	double	y_incr;
	double	x_first;
	double	y_first;
	double	i;

	y_incr = TILE;
	x_incr = TILE / tan(alpha);
	y_first = floor(player->pos[1] / TILE) * TILE;
	if (alpha > 0 && alpha < M_PI)
		y_first += TILE;
	else
		y_incr = TILE * -1;
	x_first = ((y_first - player->pos[1]) / tan(alpha)) + player->pos[0];
	i = 0;
	if ((alpha > (M_PI / 2) && alpha < (3 * M_PI) / 2 && x_incr > 0)
		|| (!(alpha > (M_PI / 2) && alpha < (3 * M_PI) / 2) && x_incr < 0)) // check x_step value
  		x_incr *= -1;
	while (!hit_wall(x_first + (x_incr * i),
			y_first + (y_incr * i) + (y_incr / TILE), map))
		i++;
	// printf("dist = %f\n", sqrt(pow((player->pos[0] - x_first) + x_incr * i, 2) + pow((y_first - player->pos[1]) + y_incr * i, 2)));
	return (sqrt(pow((player->pos[0] - x_first) + x_incr * i, 2) + pow((y_first - player->pos[1]) + y_incr * i, 2)));
}

double	v_intersect_dist(double alpha, t_map *map, t_player *player)
{
	double	x_incr;
	double	y_incr;
	double	x_first;
	double	y_first;
	double	i;

	x_incr = TILE;
	y_incr = TILE * tan(alpha);
	x_first = floor(player->pos[0] / TILE) * TILE;
	if (!(alpha > M_PI / 2 && alpha < 3 * M_PI / 2))
		x_first += TILE;
	else
		x_incr = TILE * -1;
	y_first = ((player->pos[0] - x_first) * tan(alpha)) + player->pos[1];
	if ((alpha < M_PI && alpha > 0 && y_incr < 0)
		|| (!(alpha < M_PI && alpha > 0) && y_incr > 0))
  		y_incr *= -1;
	i = 0;
	while (!hit_wall(x_first + (x_incr * i) + (x_incr / TILE),
		y_first + (y_incr * i), map))
		i++;
	// printf("dist = %f\n", sqrt(pow((player->pos[0] - x_first) + x_incr * i, 2) + pow((y_first - player->pos[1]) + y_incr * i, 2)));
	return (sqrt(pow((player->pos[0] - x_first) + x_incr * i, 2) + pow((y_first - player->pos[1]) + y_incr * i, 2)));
}

double	distance_to_wall(double alpha, t_map *map, t_player *player, char *dir)
{
	double	v_dist;
	double	h_dist;
	double	dist;

	v_dist = h_intersect_dist(alpha, map, player);
	h_dist = v_intersect_dist(alpha, map, player);
	if (v_dist < h_dist)
	{
		dist = v_dist;
		if (alpha > M_PI / 2 && alpha < 3 * M_PI / 2)
			*dir = 'E';
		else
			*dir = 'W';
	}
	else
	{
		dist = h_dist;
		if (alpha > 0 && alpha < M_PI)
			*dir = 'S';
		else
			*dir = 'N';
	}
	return (dist);
}

void	wall_height(double dist, double *wall, double *top, double *bottom)
{
	*wall = (TILE / dist) * ((DIM_W / 2) / tan(FOV *M_PI / 180 / 2));
	printf("wall height = %f\n", *wall);
	*top = (DIM_H / 2) - (*wall / 2);
	*bottom = (DIM_H / 2) + (*wall / 2);
	if (*top < 0)
		*top = 0;
	if (*bottom > DIM_H)
		*bottom = DIM_H;
}

void	render_wall(double x, double dist, t_mlx *mlx, char dir)
{
	int		y;
	double	wall;
	double	top;
	double	bottom;

	y = 0;

	wall_height(dist, &wall, &top, &bottom);
	printf("ray %f, top at %f, bottom at %f\n", x, top, bottom);
	while (y < top)
		put_pixel(mlx, x, y++, 0xF0FFFF);
	while (y < top + wall)
	{
		if (dir == 'N' || dir == 'S')
			put_pixel(mlx, x, y++, 0xFFC300);
		else
			put_pixel(mlx, x, y++, 0xDAF7A6);
	}
	while (y < DIM_H)
		put_pixel(mlx, x, y++, 0xF0FFFF);
}

void	put_map(t_data *data, t_map *map, t_player *player)
{
	// printf("----calculating distances-----\n");
	double	curr_angle;
	double	angle_increment;
	int		x;
	double	distance;
	char	dir;


	player->alpha = cardinal_to_angle(map->orientation);
	// printf("player facing %c => %f\n", map->orientation, player->alpha);
	angle_increment = ((double) FOV / (double) DIM_W ) * (M_PI / 180);
	curr_angle = normalize_angle(player->alpha - ((FOV / 2) * (M_PI / 180)));
	x = 0;
	while (x < DIM_W)
	{
		// printf("ray #%d, angle = %f\n", x, normalize_angle(curr_angle) * (180 / M_PI));
		distance = distance_to_wall(curr_angle, map, player, &dir);
		// printf("distance to wall = %f\n\n", distance);
		// distance *= cos(normalize_angle(curr_angle - player->alpha));
		render_wall(x, distance, &data->mlx, dir);
		curr_angle = normalize_angle(curr_angle + angle_increment);
		x ++;
	}
	printf("\n");
}
