/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:00:26 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 20:44:39 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if ((line[i] && line[i] == '\n') || !line[i])
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'W'
				|| line[i] == 'E' || line[i] == 'S'
				|| line[i] == 'N' || line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int	rows_cols(t_map *map, int fd, char *line)
{
	size_t	cols;

	map->rows = 0;
	map->cols = 0;
	while (line)
	{
		map->rows++;
		cols = 0;
		while (line[cols] && line[cols] != '\n')
			cols++;
		if (cols > map->cols)
			map->cols = cols;
		if (!check_map_line(line))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	// printf("cols: %i, rows: %i\n", map->cols, map->rows);
	return (map->cols * map->rows);
}

void	assign_floor_cieling(t_map *map, char type, int rgb_vals[3])
{
	if (type == 'C')
	{
		map->ceiling[0] = rgb_vals[0];
		map->ceiling[1] = rgb_vals[1];
		map->ceiling[2] = rgb_vals[2];
	}
	else if (type == 'F')
	{
		map->floor[0] = rgb_vals[0];
		map->floor[1] = rgb_vals[1];
		map->floor[2] = rgb_vals[2];
	}
}

int	read_f_c(t_map *map, char type, char *data)
{
	char	**rgb;
	int		rgb_vals[3];
	int		res;

	res = 0;
	if ((type == 'F' && map->floor[0] != -1)
		|| (type == 'C' && map->ceiling[0] != -1))
		return (res);
	rgb = ft_split(data, ',');
	if (rgb[0] && rgb[1] && rgb[2]
		&& str_isdigits(rgb[0]) && str_isdigits(rgb[1]) && str_isdigits(rgb[2]))
	{
		rgb_vals[0] = ft_atoi(rgb[0]);
		rgb_vals[1] = ft_atoi(rgb[1]);
		rgb_vals[2] = ft_atoi(rgb[2]);
		if (rgb_vals[0] >= 0 && rgb_vals[0] <= 255
			&& rgb_vals[1] >= 0 && rgb_vals[1] <= 255
			&& rgb_vals[2] >= 0 && rgb_vals[2] <= 255)
		{
			res = 1;
			assign_floor_cieling(map, type, rgb_vals);
		}
	}
	free_double_pointer((void **) rgb);
	return (res);
}

int	read_texture(t_map *map, char *dir, char *data)
{
	int	fd;
	int	res;

	res = 1;
	fd = open(data, O_RDONLY);
	if (fd < 0)
		return (-1);
	close (fd);
	if (!ft_strcmp(dir, "NO") && map->north == 0)
		map->north = ft_strdup(data);
	else if (!ft_strcmp(dir, "SO") && map->south == 0)
		map->south = ft_strdup(data);
	else if (!ft_strcmp(dir, "EA") && map->east == 0)
		map->east = ft_strdup(data);
	else if (!ft_strcmp(dir, "WE") && map->west == 0)
		map->west = ft_strdup(data);
	else
		res = 0;
	return (res);
}
