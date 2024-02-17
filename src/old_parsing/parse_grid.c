/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:22:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 22:20:47 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	flood_fill(int **grid, t_map *map, size_t i, size_t j)
{
	// printf("checking %i,%i\n", i, j);
	if ((!i && !grid[i][j]) || (!j && !grid[i][j])
		||( i == map->rows - 1 && !grid[i][j])
		||( j == map->cols - 1 && !grid[i][j]))
		return (0);
	if (grid[i][j] == 3 || grid[i][j] == 1)
		return (1);
	if (grid[i][j] == -1)
		return (0);
	grid[i][j] = 3;
	if (flood_fill(grid, map, i + 1, j)
		&& flood_fill(grid, map, i - 1, j)
		&& flood_fill(grid, map, i, j + 1)
		&& flood_fill(grid, map, i, j - 1)
	)
		return (1);
	return (0);
}

int	closed_map(t_map *map)
{
	int		**temp;
	size_t	i;
	size_t	j;

	i = 0;
	printf("---flood fill---\n");
	temp = (int **)malloc(map->rows * sizeof(int *));
	while (i < map->rows)
	{
		j = 0;
		temp[i] = (int *)malloc(sizeof(int) * map->cols);
		while (j < map->cols)
		{
			temp[i][j] = map->grid[i][j];
			j++;
		}
		i++;
	}
	i = flood_fill(temp, map, map->pos[1], map->pos[0]);
	printf("flood fill result = %li\n", i);
	free_double_pointer_size((void **) temp, map->rows);
	printf("closed map done\n");
	return (i);
}

int	read_row(t_map *map, char *row, int i)
{
	size_t	j;

	j = 0;
	map->grid[i] = (int *)malloc(sizeof(int) * map->cols);
	if (!map->grid[i])
		return (0);
	while (j < map->cols)
	{
		// printf("  %li\n", j);
		if (j < ft_strlen(row) && row[j] == '1')
			map->grid[i][j] = 1;
		else if (j < ft_strlen(row) && row[j] == '0')
			map->grid[i][j] = 0;
		else if (j < ft_strlen(row) && (row[j] == 'N'
				|| row[j] == 'S' || row[j] == 'E'
				|| row[j] == 'W'))
		{
			if (map->pos[0] != -1)
				return (0);
			map->pos[0] = j;
			map->pos[1] = i;
			map->grid[i][j] = 2;
			map->dir = row[j];
		}
		else
			map->grid[i][j] = -1;
		j++;
	}
	return (1);
}

int	init_grid(t_map *map, char *filename, size_t start)
{
	size_t	i;
	int		fd;
	char	*row;

	fd = open(filename, O_RDONLY);
	map->grid = (int **)malloc(sizeof(int *) * map->rows);
	if (!map->grid)
		return (0);
	i = 0;
	row = get_next_line(fd);
	printf("rows: %li, start: %li\n", map->rows, start);
	while (i < map->rows + start)
	{
		// printf("%li\n", i);
		if (i >= start && !read_row(map, row, i - start))
			return (0);
		i++;
		free(row);
		row = get_next_line(fd);
	}
	return (1);
}

int	parse_grid(t_map *map, char *filename, int i)
{
	if (!init_grid(map, filename, i))
		return (0);
	if (!closed_map(map))
	{
		printf("open map\n");
		return (0);
	}
	print_grid(map);
	return (1);
}
