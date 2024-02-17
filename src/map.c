/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:27:28 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 16:38:22 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	find_playerpos(t_map *map_data, int i, int j, bool pos)
{
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (ft_strchr(DIRECTION, map_data->map[i][j]) != NULL)
			{
				if (pos == true)
					return (false);
				pos = true;
				map_data->player_y = i;
				map_data->player_x = j;
				map_data->orientation = map_data->map[i][j];
			}
			j++;
		}
		i++;
	}
	return (pos);
}

//Loop through content as soon as we find a 1 as first char.
//Validate line by line and add string to the map.
//Return false if an error is encountered.
bool	loop_parse_map(char **content, t_map *map_data, int i)
{
	int	index;

	index = 0;
	map_data->map = ft_calloc(sizeof(char *), map_data->map_height + 1);
	while (index < map_data->map_height)
	{
		if (check_valid_mapline(content[index + i], 0, 0) == -1)
			return (print_msg("Error\nMap has Invalid char\n", 1));
		map_data->map[index] = copy_line_dup(content[i + index],
				map_data->map_width);
		index++;
	}
	if (find_playerpos(map_data, 0, 0, false) == false)
		return (print_msg("Error\nplayer position invalid\n", 1));
	return (check_closed_map(map_data, 0, 0));
}

//Check if the map is the last info of the file. Return -1 if its not.
int	check_map_order_char(char **array, int start)
{
	int	j;
	int	cpy;

	cpy = start;
	while (array[start])
	{
		j = 0;
		while (array[start][j])
		{
			if (array[start][j] != ' ' && array[start][j] != '\n')
				return (-1);
			j++;
		}
		start++;
	}
	return (cpy);
}

//Return the index representing the end of the map.
//-1 if an error is encountered.
int	get_map_end(char **array, int start, int j, t_map *map_data)
{
	int	len;

	map_data->map_width = 0;
	while (array[start])
	{
		j = 0;
		len = ft_strlen(array[start]);
		if (len >= map_data->map_width)
			map_data->map_width = len;
		while (array[start][j] == ' ')
			j++;
		if (check_valid_tile(array[start][j]) == false)
			return (-1);
		if (array[start][j] != '1')
			break ;
		start++;
	}
	return (check_map_order_char(array, start));
}

//Trim spaces, skip positions, parse map file and validate.
//Return false if an error is encountered.
bool	parsing_valid_map_data(char **array, t_map *map_data)
{
	int	i;
	int	ret;

	i = 0;
	while (array[i])
	{
		ret = determine_line_type(array[i]);
		if (ret == 1)
			break ;
		i++;
	}
	if (ret != 1)
		return (print_msg("Error\nInvalid Map\n", 1));
	ret = get_map_end(array, i, 0, map_data);
	map_data->map_height = ret - i;
	if (map_data->map_height < 3)
		return (print_msg("Error\nInvalid Map\n", 1));
	return (loop_parse_map(array, map_data, i));
}
