/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:34:41 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/13 21:11:17 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(int keycode, t_player *player, t_map *map)
{
	if ((keycode == DOWN || keycode == 1)
		&& !hit_wall(player->pos[0] - SPEED * cos(player->alpha) - 20,
			player->pos[1] - SPEED * sin(player->alpha) - 20, map))
	{
		player->pos[0] -= SPEED * cos(player->alpha);
		player->pos[1] -= SPEED * sin(player->alpha);
	}
	else if ((keycode == UP || keycode == 13)
		&& !hit_wall(player->pos[0] + SPEED * cos(player->alpha) + 20,
			player->pos[1] + SPEED * sin(player->alpha) + 20, map))
	{
		player->pos[0] += SPEED * cos(player->alpha);
		player->pos[1] += SPEED * sin(player->alpha);
	}
}

int	key_down(int keycode, t_cub *data)
{
	if (keycode == ESC)
		destroy_cub(data);
	else if (keycode == DOWN || keycode == 1)
		movement(keycode, &data->player, &data->game.map);
	else if (keycode == UP || keycode == 13)
		movement(keycode, &data->player, &data->game.map);
	else if (keycode == LEFT || keycode == 0)
		data->player.alpha -= (ROT * M_PI / 180);
	else if (keycode == RIGHT || keycode == 2)
		data->player.alpha += (ROT * M_PI / 180);
	render(data);
	return (0);
}
