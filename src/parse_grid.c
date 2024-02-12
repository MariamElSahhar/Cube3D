/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:22:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/12 11:22:30 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int flood_fill(int **grid, int i, int j) {
    printf("checking %i,%i\n", i, j);
    if (grid[i][j] == 3 || grid[i][j] == 1)
        return (1);
    if (grid[i][j] == -1)
        return (0);
    grid[i][j] = 3;
    if (flood_fill(grid, i + 1, j)
        && flood_fill(grid, i - 1, j)
        && flood_fill(grid, i, j + 1)
        && flood_fill(grid, i, j - 1)
    )
        return (1);
    return (0);
}

int closed_map(t_map *map) {
    int **temp;
    int i;
    int j;

    i = 0;
    printf("---flood fill---\n");
    temp = (int **)malloc(sizeof(int) * map->rows);
    while (i < map->rows) {
        j = 0;
        temp[i] = (int *)malloc(sizeof(int) * map->cols);
        while (j < map->cols) {
            temp[i][j] = map->grid[i][j];
            j++;
        }
        i++;
    }
    i = flood_fill(temp, map->pos[1], map->pos[0]);
    printf("flood fill result = %i\n", i);
    free_double_pointer_size((void **) temp, map->rows);
    printf("closed map done\n");
    return (i);
}

int	read_row(t_map *map, char *row, int i)
{
	int		j;

	j = 0;
	map->grid[i] = (int *)malloc(sizeof(int) * map->cols);
    if (!map->grid[i])
        return (0);
	while (j < map->cols)
	{
        if (row[j] && row[j] == '1')
    		map->grid[i][j] = 1;
        else if (row[j] && row[j] == '0') 
    		map->grid[i][j] = 0;
        else if (row[j] && (row[j] == 'N' || row[j] == 'S' || row[j] == 'E' || row[j] == 'W')) {
            if (map->pos[0] != -1)
                return (0);
            map->pos[0] = j;
            map->pos[1] = i;
            map->grid[i][j] = 2;
        }
        else 
            map->grid[i][j] = -1;
		j++;
	}
    return (1);
}

int init_grid(t_map *map, char *filename, int start) {
    int     i;
    int     fd;
    char    *row;

    fd = open(filename, O_RDONLY);
    map->grid = (int **)malloc(sizeof(int *) * map->rows);
	if (!map->grid)
		return (0);
	i = 0;
    row = get_next_line(fd);
	while (i < map->rows + start)
	{
        if (i >= start && !read_row(map, row, i - start))
            return (0);
        i++;
		free(row);
        row = get_next_line(fd);
	}
    return (1);
}

int parse_grid(t_map *map, char *filename, int i) {
    if(!init_grid(map, filename, i))
        return (0);
    if (!closed_map(map)) {
        printf("open map\n");   
        return (0);
    }
    print_grid(map);
    return (1);
}