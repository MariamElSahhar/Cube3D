/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:36:06 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 17:26:03 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*color_trim(char **value, int i, char *result)
{
	if (result == NULL)
		result = ft_trim_string(value[i], ' ');
	else
	{
		printf("Wrong\nCeilling or floor color duplicate\n");
		free(result);
		return (NULL);
	}
	return (result);
}

static char	*find_cube_color(char **array, char type)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	save = NULL;
	while (array[i])
	{
		j = 0;
		while (array[i][j] == ' ')
			j++;
		if (array[i][j] == type)
		{
			save = color_trim(array, i, save);
			if (save == NULL)
				return (NULL);
		}
		i++;
	}
	if (save == NULL)
		printf("Wrong\nCeilling or floor color not found\n");
	return (save);
}

bool	is_valid_cube_colorline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (false);
		i++;
	}
	return (true);
}

bool	color_cube_loop(char **numbers, int *color)
{
	int	i;

	i = 0;
	while (numbers[i])
	{
		if (is_valid_cube_colorline(numbers[i]) == false)
			return (false);
		color[i] = ft_atoi(numbers[i]);
		if (color[i] < 0 || color[i] > 255)
			return (false);
		i++;
	}
	return (true);
}

bool	valid_color_parsing(char **content, t_map *map_info, char type)
{
	char	*line;
	char	**numbers;
	int		*color;

	line = find_cube_color(content, type);
	if (!line)
		return (false);
	numbers = ft_split(line + 1, ',');
	free(line);
	if (count_map_size(numbers) != 3)
		return (free_color(numbers));
	color = malloc(sizeof(int) * 3);
	if (color_cube_loop(numbers, color) == false)
	{
		free(color);
		return (free_color(numbers));
	}
	if (type == 'F')
		map_info->floor = color;
	else
		map_info->ceiling = color;
	ft_free_array(numbers);
	return (true);
}
