/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:34:41 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/12 19:01:16 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(int keycode, t_player *player, t_map *map)
{
	if (keycode == DOWN)
	{
		if (player->pos[0] - SPEED * cos(player->alpha) > 0)
			player->pos[0] -= SPEED * cos(player->alpha);
		if (player->pos[1] - SPEED * sin(player->alpha) > 0)
			player->pos[1] -= SPEED * sin(player->alpha);
	}
	else if (keycode == UP)
	{
		if (player->pos[0] + SPEED * cos(player->alpha) < map->map_width * TILE)
			player->pos[0] += SPEED * cos(player->alpha);
		if (player->pos[1] + SPEED * sin(player->alpha) < map->nline * TILE)
			player->pos[1] += SPEED * sin(player->alpha);
	}
}

int	key_down(int keycode, t_cub *data)
{
	if (keycode == ESC)
		destroy_cub(data);
	if (keycode == DOWN || keycode == UP)
		movement(keycode, &data->player, &data->game.map);
	else if (keycode == LEFT)
		data->player.alpha -= (ROT * M_PI / 180);
	else if (keycode == RIGHT)
		data->player.alpha += (ROT * M_PI / 180);
	render(data);
	return (0);
}
