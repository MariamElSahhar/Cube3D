/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:34:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/13 21:14:34 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int init_data(t_data *data, char *filename) {
	data->map = parse_map(filename);
		if (!data->map)
			return (0);
	data->mlx = (t_mlx*)ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx)
		return (0);
	data->mlx->mlx = mlx_init();
	data->mlx->img = mlx_new_image(data->mlx->mlx, DIM_W, DIM_H);
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &(data->mlx->bits_per_pixel), &(data->mlx->line_length), &(data->mlx->endian));
	data->mlx->mlx_win = mlx_new_window(data->mlx->mlx, DIM_W, DIM_H, "Hello World");
	return (1);
}

void	render(t_data *data) {
	if (data->mlx->img != 0)
		mlx_destroy_image(data->mlx, data->mlx->img);
	mlx_clear_window(data->mlx, data->mlx->mlx_win);
	data->mlx->img = mlx_new_image(data->mlx, DIM_W, DIM_H);
	data->mlx->addr = mlx_get_data_addr(data->mlx->img, &(data->mlx->bits_per_pixel),
			&(data->mlx->line_length), &(data->mlx->endian));
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img, 0, 0);
	put_map(data);
}


int main(int argc, char ** argv) {
	t_data	data;

	if (argc == 2) {
		if (!init_data(&data, argv[1]))
			return (1);
		render(&data);
		mlx_loop(&data.mlx);
	}
	
	
	return (0);
}
