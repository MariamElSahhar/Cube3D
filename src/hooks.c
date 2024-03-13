/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:34:41 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/13 17:40:28 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <time.h>

void	movement(int keycode, t_player *player, t_map *map)
{
	printf("\n%li movement\n", time(NULL));
	if (keycode == DOWN
		&& !hit_wall(player->pos[0] - SPEED * cos(player->alpha) - 20,
			player->pos[1] - SPEED * sin(player->alpha) - 20, map))
	{
		player->pos[0] -= SPEED * cos(player->alpha);
		player->pos[1] -= SPEED * sin(player->alpha);
	}
	else if (keycode == UP
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
	else if (keycode == DOWN || keycode == UP)
		movement(keycode, &data->player, &data->game.map);
	else if (keycode == LEFT)
		data->player.alpha -= (ROT * M_PI / 180);
	else if (keycode == RIGHT)
		data->player.alpha += (ROT * M_PI / 180);
	render(data);
	return (0);
}
