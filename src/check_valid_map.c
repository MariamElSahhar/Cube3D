/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:54:40 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/28 21:33:17 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	is_valid_zero(int c, int y, int x, t_cub *cub)
{
	char	*pre;
	char	*next;

	pre = ft_strdup(cub->game.map.map_2d[y - 1]);
	next = ft_strdup(cub->game.map.map_2d[y + 1]);
	if (pre[ft_strlen(pre) - 1] == '\n')
		pre[ft_strlen(pre) - 1] = 0;
	if (next[ft_strlen(next) - 1] == '\n')
		next[ft_strlen(next) - 1] = 0;
	if (c == '0')
	{
		if ((x + 1) > ft_strlen(pre) || (x + 1) > ft_strlen(next))
		{
			free(pre);
			free(next);
			print_error("Invalid map", cub);
		}
	}
	free(pre);
	free(next);
	return ;
}

void	get_player_pos(int c, int y, int x, t_cub *cub)
{
	char		*pre;
	char		*next;
	static int	err;

	pre = ft_strdup(cub->game.map.map_2d[y - 1]);
	next = ft_strdup(cub->game.map.map_2d[y + 1]);
	if (pre[ft_strlen(pre) - 1] == '\n')
		pre[ft_strlen(pre) - 1] = 0;
	if (next[ft_strlen(next) - 1] == '\n')
		next[ft_strlen(next) - 1] = 0;
	if (cub->game.map.player_dir)
		err = -1;
	cub->game.map.player_x = x;
	if (x + 1 > ft_strlen(pre) || x + 1 > ft_strlen(next))
		err = -2;
	if (err == -1 || err == -2)
	{
		free(pre);
		free(next);
		print_error("Invalid player", cub);
	}
	cub->game.map.player_y = y;
	cub->game.map.player_dir = c;
	free(pre);
	free(next);
}

void	check_map_line(int y, t_cub *cub)
{
	int	x;

	x = 0;
	// if (y != 0 || y != cub->game.map.nline - 1)
	// 	check_map_edge(cub->game.map.map_2d[y], cub);
	while (cub->game.map.map_2d && cub->game.map.map_2d[y][x])
	{
		is_valid_char(y, cub->game.map.map_2d[y][x], cub);
		check_map_edge(cub->game.map.map_2d[y], cub);
		if (y == cub->game.map.nline - 1)
			check_map_edge(cub->game.map.map_2d[y], cub);
		if (y != 0 && y != cub->game.map.nline - 1)
			is_valid_zero(cub->game.map.map_2d[y][x], y, x, cub);
		check_is_space(cub->game.map.map_2d[y][x], y, x, cub);
		if (check_is_player(cub->game.map.map_2d[y][x]))
			get_player_pos(cub->game.map.map_2d[y][x], y, x, cub);
		x++;
	}
	return ;
}

void	check_map(t_cub *cub)
{
	int	y;

	y = 0;
	while (cub->game.map.map_2d && cub->game.map.map_2d[y])
	{
		check_map_line(y, cub);
		y++;
	}
	return ;
}

void	get_map_width(t_cub *cub)
{
	int	y;

	y = 0;
	while (cub->game.map.map_2d[y])
	{
		if (ft_strlen(cub->game.map.map_2d[y]) > cub->game.map.map_width)
			cub->game.map.map_width = ft_strlen(cub->game.map.map_2d[y]);
		y++;
	}
	return ;
}
