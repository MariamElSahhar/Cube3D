/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 07:53:07 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/14 10:13:14 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//check if the file has .cub type
bool	check_cubfile_extention(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '.')
		{
			if (ft_strncmp(file + i, ".cub", 5) == 0)
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

//Map file in array of string
char	**get_content_2darray(char *file, int fd, char **line)
{
	int		ret;
	int		i;

	i = count_nbline_file(file);
	if (i <= 0)
		return (NULL);
	line = ft_calloc(sizeof(char *), i + 1);
    if (!line)
		return (NULL);
	fd = open(file, O_RDONLY);
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, line + i);
		if (ret < 0)
		{
			close (fd);
			return (NULL);
		}
		i++;
	}
	close (fd);
	return (line);
}

//Parsing map file with argv[1]
bool	parsing_main_map(char **argv, t_map *map_info)
{
	char	**content;

	content = get_content_2darray(argv[1], 0, NULL);
	if (!content)
	{
		free(map_info);
		return (print_msg("Error\nreading map file\n", 1));
	}
	if (is_valid_content(content) == false
		|| parsing_valid_map_data(content, map_info) == false
		|| texture_parsing(content, map_info) == false
		|| valid_color_parsing(content, map_info, 'F') == false
		|| valid_color_parsing(content, map_info, 'C') == false)
	{
		ft_free_array(content);
		free_map(map_info);
		return (false);
	}
	ft_free_array(content);
	return (true);
}
