/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:34:41 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/18 12:25:35 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(int keycode, t_player *player, t_map *map)
{
	if ((keycode == DOWN || keycode == KEY_S)
		&& !hit_wall(player->pos[0] - SPEED * cos(player->alpha) * 2,
			player->pos[1] - SPEED * sin(player->alpha) * 2, map))
	{
		player->pos[0] -= SPEED * cos(player->alpha);
		player->pos[1] -= SPEED * sin(player->alpha);
	}
	else if ((keycode == UP || keycode == KEY_W)
		&& !hit_wall(player->pos[0] + SPEED * 2 * cos(player->alpha),
			player->pos[1] + SPEED * 2 * sin(player->alpha), map))
	{
		player->pos[0] += SPEED * cos(player->alpha);
		player->pos[1] += SPEED * sin(player->alpha);
	}
}

void	side_movement(int keycode, t_player *player, t_map *map)
{
	if (keycode == KEY_D
		&& !hit_wall(player->pos[0] - SPEED * cos(player->alpha - M_PI / 2),
			player->pos[1] - SPEED * sin(player->alpha - M_PI / 2), map))
	{
		player->pos[0] = player->pos[0] - SPEED * cos(player->alpha - M_PI / 2);
		player->pos[1] = player->pos[1] - SPEED * sin(player->alpha - M_PI / 2);
	}
	else if (keycode == KEY_A
		&& !hit_wall(player->pos[0] + SPEED * cos(player->alpha - M_PI / 2),
			player->pos[1] + SPEED * sin(player->alpha - M_PI / 2), map))
	{
		player->pos[0] = player->pos[0] + SPEED * cos(player->alpha - M_PI / 2);
		player->pos[1] = player->pos[1] + SPEED * sin(player->alpha - M_PI / 2);
	}
}

int	key_down(int keycode, t_cub *data)
{
	if (keycode == ESC)
		destroy_cub(data);
	else if (keycode == DOWN || keycode == 1 || keycode == UP || keycode == 13)
		movement(keycode, &data->player, &data->game.map);
	else if (keycode == LEFT)
		data->player.alpha = normalize_angle(data->player.alpha - (ROT * M_PI / 180));
	else if (keycode == RIGHT)
		data->player.alpha = normalize_angle(data->player.alpha + (ROT * M_PI / 180));
	else if (keycode == KEY_A || keycode == KEY_D)
		side_movement(keycode, &data->player, &data->game.map);
	render(data);
	return (0);
}
