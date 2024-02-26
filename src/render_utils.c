/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:10:15 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/26 19:40:43 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	normalize_angle(double angle)
{
	double	norm;

	norm = fmod(angle, 2 * M_PI);
	if (norm < 0)
		norm += 2 * M_PI;
	return norm;
}

double	cardinal_to_angle(char dir)
{
	double	angle;

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

int	hit_wall(double x, double y, t_map *map)
{
	int	x_coor;
	int	y_coor;

	x_coor = floor(x / TILE);
	y_coor = floor(y / TILE);
	if (x_coor < 0 || y_coor < 0 ||
		x_coor >= map->map_width || y_coor >= map->map_height)
		return (1);
	if (map->map[y_coor][x_coor] &&
		map->map[y_coor][x_coor] == '1')
		return (1);
	return (0);
}

