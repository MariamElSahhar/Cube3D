/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:10:15 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/12 10:30:58 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	normalize_angle(double angle)
{
	double	norm;

	norm = fmod(angle, 2 * M_PI);
	if (norm < 0)
		norm += (2 * M_PI);
	return norm;
}

double	cardinal_to_angle(char dir)
{
	double	angle;

	angle = -1.0;
	if (dir == 'N')
		angle = M_PI / 2;
	else if (dir == 'S')
		angle = 3 * M_PI / 2;
	else if (dir == 'E')
		angle = 0;
	else if (dir == 'W')
		angle = M_PI;
	return (angle);
}

int	hit_wall(double x, double y, t_map *map)
{
	int	x_coor;
	int	y_coor;

	x_coor = floor(x / TILE);
	y_coor = floor(y / TILE);
	if (x_coor < 0 || y_coor < 0 ||
		x_coor >= map->map_width || y_coor >= map->nline ||
		!map->map_2d[y_coor] ||
		x_coor >= (int) ft_strlen(map->map_2d[y_coor]))
		return (1);
	if (map->map_2d[y_coor][x_coor] &&
		map->map_2d[y_coor][x_coor] == '1')
		return (1);
	return (0);
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
