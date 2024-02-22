/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:10:15 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/22 21:35:23 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	normalize_angle(double angle)
{
	double norm = fmod(angle, 2 * M_PI);

	if (norm < 0)
	{
		norm += 2 * M_PI;
	}
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
	printf("checking map for intersection at %i, %i --> \n", x_coor, y_coor);
	if (map->map[y_coor][x_coor] == '1') {
		printf("wall here\n");
		return (1);
	}
	printf("no wall here\n");
	return (0);
}
