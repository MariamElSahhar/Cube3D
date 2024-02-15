/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:29:37 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 20:51:27 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_grid(t_map *map)
{
	size_t	i;
	size_t	j;

	printf("NO %s\n", map->north);
	printf("SO %s\n", map->south);
	printf("EA %s\n", map->east);
	printf("WE %s\n", map->west);
	printf("F %i,%i,%i\n", map->floor[0], map->floor[1], map->floor[2]);
	printf("C %i,%i,%i\n", map->ceiling[0], map->ceiling[1], map->ceiling[2]);
	printf("Dir %c\n", map->dir);
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == -1)
				printf(" ");
			else
				printf("%i", map->grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

char	*skip_empty_lines(int fd, char *line, int *i)
{
	char	*trim;
	int		empty;

	empty = 1;
	while (line && empty)
	{
		trim = ft_strtrim(line, " ");
		if (trim[0] != '\n')
			empty = 0;
		else
		{
			*i = *i + 1;
			free(line);
			line = get_next_line(fd);
		}
		free(trim);
	}
	return (line);
}

int	map_data_complete(t_map *map)
{
	if (map->floor[0] == -1 || map->ceiling[0] == -1 || !map->north
		|| !map->south || !map->east || !map->west)
		return (0);
	return (1);
}

int	str_isdigits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
