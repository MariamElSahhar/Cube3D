/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:40:04 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 20:42:12 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	read_map_line(t_map *map, char *line)
{
	char	**data;
	char	*tmp;
	int		res;

	res = -1;
	tmp = ft_strtrim(line, "\n");
	data = ft_split(tmp, ' ');
	free(tmp);
	if (!data[0])
		res = 1;
	else if (!data[1] || data[2])
	{
		printf("incorrect line\n");
		res = 0;
	}
	else if (!ft_strcmp(data[0], "F") || !ft_strcmp(data[0], "C"))
	{
		res = read_f_c(map, data[0][0], data[1]);
		printf("F/C res %i\n", res);
	}
	else if (!ft_strcmp(data[0], "NO") || !ft_strcmp(data[0], "EA")
		|| !ft_strcmp(data[0], "WE") || !ft_strcmp(data[0], "SO"))
	{
		res = read_texture(map, data[0], data[1]);
		printf("texture res %i\n", res);
	}
	free_double_pointer((void **) data);
	return (res);
}

t_map	*init_map(t_map *map)
{
	map->floor[0] = -1;
	map->ceiling[0] = -1;
	map->pos[0] = -1;
	map->east = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	return (map);
}

int	read_map(t_map *map, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line && !map_data_complete(map))
	{
		if (!read_map_line(map, line))
		{
			printf("wrong map format\n");
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	line = skip_empty_lines(fd, line, &i);
	if (!rows_cols(map, fd, line))
		return (0);
	if (map->rows < 3 || map->cols < 3)
	{
		printf("invalid map\n");
		return (0);
	}
	return (i);
}

int	parse_map(char *filename, t_map *map)
{
	int	fd;
	int	map_start;

	map = init_map(map);
	if (!map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to read file\n");
		return (0);
	}
	map_start = read_map(map, fd);
	if (!map_start)
		return (0);
	if (!parse_grid(map, filename, map_start))
		return (0);
	printf("slay\n");
	return (1);
}
