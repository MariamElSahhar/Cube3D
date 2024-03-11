/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:44:14 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/11 21:12:43 by melsahha         ###   ########.fr       */
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

int inter_check(double angle, double *inter, double *step, int is_horizon) // check the intersection
{
 if (is_horizon)
 {
  if (angle > 0 && angle < M_PI)
  {
   *inter += TILE;
   return (-1);
  }
  *step *= -1;
 }
 else
 {
  if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
  {
   *inter += TILE;
   return (-1);
  }
  *step *= -1;
 }
 return (1);
}

double	h_intersect_dist(double alpha, t_map *map, t_player *player)
{
	double	x_incr;
	double	y_incr;
	double	x_first;
	double	y_first;
	double	pix;

	y_incr = TILE;
	x_incr = TILE / tan(alpha);
	y_first = floor(player->pos[1] / TILE) * TILE;
	pix = inter_check(alpha, &y_first, &y_incr, 1);
	x_first = ((y_first - player->pos[1]) / tan(alpha)) + player->pos[0];
	if ((alpha > (M_PI / 2) && (alpha < (3 * M_PI / 2)) && x_incr > 0)
		|| (!(alpha > (M_PI / 2) && alpha < (3 * M_PI) / 2) && x_incr < 0))
  		x_incr *= -1;
	while (!hit_wall(x_first, y_first - pix, map))
	{
		x_first += x_incr;
		y_first += y_incr;
	}
	printf("h_inter at (%f, %f)\n", floor(x_first / TILE), floor(y_first / TILE));
	// printf("h_inter: dist = %f\n",sqrt(pow((player->pos[0] - x_first) + x_incr * i, 2) + pow((y_first - player->pos[1]) + y_incr * i, 2)));
	return (sqrt(pow(x_first - player->pos[0], 2)
			+ pow(y_first - player->pos[1], 2)));
}

double	v_intersect_dist(double alpha, t_map *map, t_player *player)
{
	double	x_incr;
	double	y_incr;
	double	x_first;
	double	y_first;
	double	pix;

	x_incr = TILE;
	y_incr = TILE * tan(alpha);
	x_first = floor(player->pos[0] / TILE) * TILE;
	pix = inter_check(alpha, &x_first, &x_incr, 0);
	y_first = ((x_first - player->pos[0]) * tan(alpha)) + player->pos[1];
	if ((alpha < M_PI && alpha > 0 && y_incr < 0)
		|| (!(alpha < M_PI && alpha > 0) && y_incr > 0))
  		y_incr *= -1;
	while (!hit_wall(x_first - pix, y_first, map))
	{
		x_first += x_incr;
		y_first += y_incr;
	}
	printf("v_inter at (%f, %f)\n", floor(x_first / TILE), floor(y_first / TILE));
	// printf("v_inter: dist = %f\n", sqrt(pow((player->pos[0] - x_first) + x_incr * i, 2) + pow((y_first - player->pos[1]) + y_incr * i, 2)));
	return (sqrt(pow(x_first - player->pos[0], 2)
			+ pow(y_first - player->pos[1], 2)));
}

double	distance_to_wall(double alpha, t_map *map, t_player *player, char *dir)
{
	double	v_dist;
	double	h_dist;
	double	dist;

	v_dist = h_intersect_dist(alpha, map, player);
	h_dist = v_intersect_dist(alpha, map, player);
	printf("h_inter = %f, v_inter = %f\n", v_dist, h_dist);
	if (v_dist < h_dist)
	{
		dist = v_dist;
		if (alpha > 0 && alpha < M_PI)
			*dir = 'S';
		else
			*dir = 'N';
	}
	else
	{
		dist = h_dist;
		if (alpha > M_PI / 2 && alpha < 3 * M_PI / 2)
			*dir = 'E';
		else
			*dir = 'W';
	}
	return (dist);
}

void	wall_height(double dist, double *wall, double *top, double *bottom)
{
	*wall = (TILE / dist) * ((DIM_W / 2) / tan(FOV * M_PI / 180 / 2));
	// printf("wall height = %f\n", *wall);
	*top = (DIM_H / 2) - (*wall / 2);
	*bottom = (DIM_H / 2) + (*wall / 2);
	if (*top < 0)
		*top = 0;
	if (*bottom > DIM_H)
		*bottom = DIM_H;
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
	if (dir == 'N' || dir == 'S')
		printf("N/S facing\n");
	if (dir == 'E' || dir == 'W')
		printf("E/W facing\n");
	while (y < top + wall)
	{
		if (dir == 'N' || dir == 'S')
			put_pixel(&data->mlx, x, y++, 0xFFC300);
		else
			put_pixel(&data->mlx, x, y++, 0xDAF7A6);
	}
	while (y < DIM_H)
		put_pixel(&data->mlx, x, y++, data->game.floor);
}

void	put_map(t_cub *data, t_map *map, t_player *player)
{
	// printf("----calculating distances-----\n");
	double	curr_angle;
	double	angle_increment;
	int		x;
	double	distance;
	char	dir;


	player->alpha = cardinal_to_angle(map->player_dir);
	// printf("player facing %c => %f\n", map->orientation, player->alpha);
	angle_increment = ((double) FOV / (double) DIM_W ) * (M_PI / 180);
	curr_angle = normalize_angle(player->alpha - ((FOV / 2) * (M_PI / 180)));
	x = 0;
	while (x < DIM_W)
	{
		printf("ray #%d, angle = %f\n", x, normalize_angle(curr_angle) * (180 / M_PI));
		distance = distance_to_wall(curr_angle, map, player, &dir);
		printf("distance to wall = %f\n\n", distance);
		// distance *= cos(normalize_angle(curr_angle - player->alpha));
		render_wall(x, distance, data, dir);
		curr_angle = normalize_angle(curr_angle + angle_increment);
		x ++;
	}
	printf("\n");
}
