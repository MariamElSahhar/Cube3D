/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:27:58 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/11 19:06:04 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_start(char const *str, int const c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
	{
		i++;
	}
	return (i);
}

static int	is_end(char const *str, int const c, int start, int len)
{
	int	end;

	end = len - 1;
	while (end > start && str[end] == c)
	{
		end--;
	}
	end++;
	return (end);
}

char	*new_strtrimchar(char const *str, int const c)
{
	int		start;
	int		end;
	char	*trim;
	int		i;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	start = is_start(str, c);
	if (start == ft_strlen(str))
		return (NULL);
	end = is_end(str, c, start, ft_strlen(str));
	if (!start && !end)
	{
		trim = ft_strdup(str);
		return (trim);
	}
	trim = (char *)malloc((end - start) + 1);
	if (!trim)
		return (NULL);
	while (start < end)
		trim[i++] = str[start++];
	trim[i] = 0;
	return (trim);
}


void	init_map(t_cub *map_data)
{
	map_data->game.north = NULL;
	map_data->game.south = NULL;
	map_data->game.west = NULL;
	map_data->game.east = NULL;
	map_data->game.floor = -1;
	map_data->game.ceiling = -1;
	map_data->game.file.fd = 0;
	map_data->game.file.nline = 0;
	map_data->game.file.line = NULL;
	map_data->game.file.file_2d = NULL;
	map_data->game.map.map_2d = NULL;
	map_data->game.map.map_pos = -1;
	map_data->game.map.nline = 0;
	map_data->game.map.player_x = -1;
	map_data->game.map.player_y = -1;
	map_data->game.map.player_dir = 0;
	map_data->game.map.map_width = 0;
	return ;
}
