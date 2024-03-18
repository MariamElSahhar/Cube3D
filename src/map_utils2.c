/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:02:20 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/18 14:27:05 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_map_space(int y, int x, t_cub *cub)
{
	if (y != 0)
		if (x <= ft_strlen(cub->game.map.map_2d[y - 1])
			&& (cub->game.map.map_2d[y - 1][x] == '0'
			|| check_is_player(cub->game.map.map_2d[y - 1][x])))
			print_error("Invalid space", cub);
	if (y != cub->game.map.nline - 1)
		if (x <= ft_strlen(cub->game.map.map_2d[y + 1])
			&& (cub->game.map.map_2d[y + 1][x] == '0'
			|| check_is_player(cub->game.map.map_2d[y + 1][x])))
			print_error("Invalid space", cub);
	if (x != 0)
		if (cub->game.map.map_2d[y][x - 1] == '0'
			|| check_is_player(cub->game.map.map_2d[y][x - 1]))
			print_error("Invalid space", cub);
	if (x != ft_strlen(cub->game.map.map_2d[y]) - 1)
		if (cub->game.map.map_2d[y][x + 1] == '0'
			|| check_is_player(cub->game.map.map_2d[y][x + 1]))
			print_error("Invalide space", cub);
	return ;
}

void	check_map_edge(char *line, t_cub *map)
{
	char	*tmp;

	tmp = copy_and_trim(line);
	if (!tmp)
		print_error("Invalid line", map);
	
	if (line == map->game.map.map_2d[0]
		|| line == map->game.map.map_2d[map->game.map.nline - 1])
	{
		if (check_map_wall(tmp))
			print_error("map not surrounded by walls", map);
	}
	if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
	{
		free(tmp);
		print_error("Map not surrounded by walls", map);
	}
	free(tmp);
	return ;
}

void	is_valid_char(int y, int c, t_cub *cub)
{
	if (c != '1' && c != ' ' && c != '\n')
	{
		if (y != 0 || y != cub->game.map.nline)
		{
			if (c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
				print_error("Invalid character", cub);
		}
		if (y == 0 || y == cub->game.map.nline - 1)
			print_error("Invalid character", cub);
	}
	return ;
}

bool	check_is_player(int c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

void	check_is_space(int c, int y, int x, t_cub *cub)
{
	if (c == ' ')
		check_map_space(y, x, cub);
	return ;
}
