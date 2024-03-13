/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:43 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/13 18:39:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_textures(t_textures textures[4], t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		textures[i].width = TILE;
		textures[i].height = TILE;
		textures[i].img = mlx_xpm_file_to_image(mlx->mlx, textures[i].path,
			&textures[i].width, &textures[i].height);
		textures[i].addr = mlx_get_data_addr(textures[i].img,
			&textures[i].bits_per_pixel, &textures[i].line_length,
			&textures[i].endian);
		i++;
	}
}

int	init_mlx(t_cub *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.img = mlx_new_image(data->mlx.mlx, DIM_W, DIM_H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&(data->mlx.bits_per_pixel), &(data->mlx.line_length),
			&(data->mlx.endian));
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			DIM_W, DIM_H, "Hello World");
	data->player.pos[0] = (data->game.map.player_x * TILE) + (TILE / 2);
	data->player.pos[1] = (data->game.map.player_y * TILE) + (TILE / 2);
	data->player.alpha = cardinal_to_angle(data->game.map.player_dir);
	data->game.textures[0].path = ft_strdup(data->game.north);
	data->game.textures[1].path = ft_strdup(data->game.east);
	data->game.textures[2].path = ft_strdup(data->game.south);
	data->game.textures[3].path = ft_strdup(data->game.west);
	load_textures(data->game.textures, &data->mlx);
	return (1);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= DIM_W || x < 0 || y >= DIM_H || y < 0)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	put_texture(t_cub *data, int x, int y, char d)
{
	t_textures	*texture;
	char	*dir;
	char	rgb[3];
	int		index;

	dir = "NESW";
	texture = &data->game.textures[ ft_getIndex(dir, d) ];
	index = ((x % texture->width) * (texture->bits_per_pixel / 8) + ((y % texture->height) * texture->width * (texture->bits_per_pixel / 8)));
	rgb[0] = texture->addr[index];
	rgb[1] = texture->addr[index + 1];
	rgb[2] = texture->addr[index + 2];
	index = (rgb[0]) | (rgb[1] << 8) | (rgb[2] << 16);
	return (index);
}

void	render_wall(double x, t_cub *data, t_ray *ray)
{
	int		y;
	double	wall;
	double	top;
	double	bottom;
	int		color;

	y = 0;
	wall_height(ray->dist, &wall, &top, &bottom);
	while (y < top)
		put_pixel(&data->mlx, x, y++, data->game.ceiling);
	while (y < bottom)
	{
		color = put_texture(data, ray->wall_x, (y - top) * (TILE / wall), ray->dir);
		put_pixel(&data->mlx, x, y++, color);
	}
	while (y < DIM_H)
		put_pixel(&data->mlx, x, y++, data->game.floor);
}
