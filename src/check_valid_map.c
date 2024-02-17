/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:54:40 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 16:24:31 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	loop_check_row(t_map *map_data, int i, int j)
{
	while (j < map_data->map_width)
	{
		if (map_data->map[i][j] == '1')
			return (true);
		if (map_data->map[i][j] == '-')
			return (false);
		j++;
	}
	return (false);
}

bool	check_wall_hor(t_map *map_data, int i, int nb_col, int j)
{
	bool	res;

	res = false;
	while (nb_col >= 0)
	{
		if (map_data->map[i][nb_col] == '1')
		{
			res = true;
			break ;
		}
		if (map_data->map[i][nb_col] == '-')
			return (false);
		if (nb_col == 0)
			break ;
		nb_col--;
	}
	if (res == false)
		return (false);
	return (loop_check_row(map_data, i, j));
}

bool	loop_check_colume(t_map *map_data, int i, int j)
{
	while (i < map_data->map_height)
	{
		if (map_data->map[i][j] == '1')
			return (true);
		if (map_data->map[i][j] == '-')
			return (false);
		i++;
	}
	return (false);
}

bool	check_wall_vert(t_map *map_info, int i, int nb_row, int j)
{
	bool	ret;

	ret = false;
	while (nb_row >= 0)
	{
		if (map_info->map[nb_row][j] == '1')
		{
			ret = true;
			break ;
		}
		if (map_info->map[nb_row][j] == '-')
			return (false);
		if (nb_row == 0)
			break ;
		nb_row--;
	}
	if (ret == false)
		return (false);
	return (loop_check_colume(map_info, i, j));
}

//Loop through the map
//Verify every direction of a position to check if it colides with a wall.
bool	check_closed_map(t_map *map_data, int i, int j)
{
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (map_data->map[i][j] != '1' && map_data->map[i][j] != '-')
			{
				if (check_wall_vert(map_data, i, i, j) == false
					|| check_wall_hor(map_data, i, j, j) == false)
					return (print_msg("Error\nMap is not closed by walls\n", 1));
			}
			j++;
		}
		i++;
	}
	return (true);
}

