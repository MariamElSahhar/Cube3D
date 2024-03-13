/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:44:14 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/13 16:07:20 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	inter_check(double angle, double *inter, double *step, int is_horizon)
{
	if (is_horizon && (angle > 0 && angle < M_PI))
	{
		*inter += TILE;
		return (-1);
	}
	else if (!is_horizon && !(angle > M_PI / 2 && angle < 3 * M_PI / 2))
	{
		*inter += TILE;
		return (-1);
	}
	else
	{
		*step *= -1;
		return (1);
	}
}

double	h_intersect_dist(double alpha, t_map *map, t_player *player, t_ray *ray)
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
	ray->wall_h = (int) fmod(x_first, TILE);
	return (sqrt(pow(x_first - player->pos[0], 2)
			+ pow(y_first - player->pos[1], 2)));
}

double	v_intersect_dist(double alpha, t_map *map, t_player *player, t_ray *ray)
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
	ray->wall_v = (int) fmod(y_first, TILE);
	return (sqrt(pow(x_first - player->pos[0], 2)
			+ pow(y_first - player->pos[1], 2)));
}

double	distance_to_wall(double alpha, t_map *map, t_player *player, t_ray *ray)
{
	double	v_dist;
	double	h_dist;
	double	dist;

	h_dist = h_intersect_dist(alpha, map, player, ray);
	v_dist = v_intersect_dist(alpha, map, player, ray);
	if (v_dist < h_dist)
	{
		ray->wall_x = ray->wall_v;
		dist = v_dist;
		if (alpha > 0 && alpha < M_PI)
			ray->dir = 'S';
		else
			ray->dir = 'N';
	}
	else
	{
		ray->wall_x = ray->wall_h;
		dist = h_dist;
		if (alpha > M_PI / 2 && alpha < 3 * M_PI / 2)
			ray->dir = 'E';
		else
			ray->dir = 'W';
	}
	return (dist);
}

void	put_map(t_cub *data, t_map *map, t_player *player)
{
	double	curr_angle;
	double	angle_increment;
	int		x;
	t_ray	ray;

	angle_increment = ((double) FOV / (double) DIM_W) * (M_PI / 180);
	curr_angle = normalize_angle(player->alpha - ((FOV / 2) * (M_PI / 180)));
	x = 0;
	while (x < DIM_W)
	{
		ray.dist = distance_to_wall(curr_angle, map, player, &ray);
		render_wall(x, data, &ray);
		curr_angle = normalize_angle(curr_angle + angle_increment);
		x ++;
	}
}
