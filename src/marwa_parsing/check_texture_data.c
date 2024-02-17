/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:09:53 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/13 16:41:32 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	find_texture_pos(char **array, char *ori, char **texture, int x)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j] == ' ')
			j++;
		if (ft_strncmp(array[i] + j, ori, 2) == 0)
		{
			if (texture[x] == NULL)
				texture[x] = ft_strtrim(array[i] + j + 2, " ");
			else
				return (false);
		}
		i++;
	}
	if (texture[x] == NULL)
		return (false);
	return (true);
}

bool	is_texture_file_xpm(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '.')
		{
			if (ft_strncmp(string + i, ".xpm", 4) == 0)
				return (true);
		}
		i++;
	}
	return (false);
}

//check if the file can be opened and if its the right type (.xpm)
bool	check_texture_file(char **texture)
{
	if (open(texture[0], O_RDONLY) == -1
		|| is_texture_file_xpm(texture[0]) == false)
		return (false);
	if (open(texture[1], O_RDONLY) == -1
		|| is_texture_file_xpm(texture[1]) == false)
		return (false);
	if (open(texture[2], O_RDONLY) == -1
		|| is_texture_file_xpm(texture[2]) == false)
		return (false);
	if (open(texture[3], O_RDONLY) == -1
		|| is_texture_file_xpm(texture[3]) == false)
		return (false);
	return (true);
}

bool	texture_parsing(char **array, t_map *map_data)
{
	map_data->texture = ft_calloc(sizeof(char *), 5);
	(void)array;
	if (find_texture(array, "NO", map_data->texture, 0) == false
		|| find_texture(array, "EA", map_data->texture, 1) == false
		|| find_texture(array, "SO", map_data->texture, 2) == false
		|| find_texture(array, "WE", map_data->texture, 3) == false)
		return (print_msg("Error\nMissing texture\n", 1));
	if (check_texture_file(map_data->texture) == false)
		return (print_msg("Error\nTexture file error\n", 1));
	return (true);
}