/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_saver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:03:28 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/28 09:42:20 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**file_to_2d(char **pre, char *line, int nline, t_cub *map)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (nline + 1));
	if (!new)
		print_error("Error", map);
	while (pre && pre[i])
	{
		new[i] = ft_strdup(pre[i]);
		free(pre[i]);
		i++;
	}
	new[i] = ft_strdup(line);
	new[i + 1] = 0;
	free(pre);
	free(line);
	return (new);
}

void	saving_map_file(t_cub *map)
{
	map->game.file.line = get_next_line(map->game.file.fd);
	if (!map->game.file.line)
		print_error("Empty File", map);
	while (map->game.file.line)
	{
		map->game.file.nline++;
		map->game.file.file_2d = file_to_2d(map->game.file.file_2d,
				map->game.file.line, map->game.file.nline, map);
		map->game.file.line = get_next_line(map->game.file.fd);
	}
	return ;
}
