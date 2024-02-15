/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:34:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 20:37:30 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_data(t_data *data, char *filename)
{
	if (!parse_map(filename, &data->map))
		return (0);
	printf("mlx init\n");
	data->mlx.mlx = mlx_init();
	printf("mlx new image\n");
	data->mlx.img = mlx_new_image(data->mlx.mlx, DIM_W, DIM_H);
	printf("mlx get data addr\n");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&(data->mlx.bits_per_pixel), &(data->mlx.line_length),
			&(data->mlx.endian));
	printf("mlx new window\n");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			DIM_W, DIM_H, "Hello World");
	printf("done data init\n");
	return (1);
}

void	render(t_data *data)
{
	if (data->mlx.img != 0)
		mlx_destroy_image(&data->mlx, data->mlx.img);
	mlx_clear_window(&data->mlx, data->mlx.mlx_win);
	data->mlx.img = mlx_new_image(&data->mlx, DIM_W, DIM_H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&(data->mlx.bits_per_pixel),
			&(data->mlx.line_length),
			&(data->mlx.endian));
	put_map(data);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
}

void	free_data(t_data *data)
{
	if (data->map.north)
		free(data->map.north);
	if (data->map.east)
		free(data->map.east);
	if (data->map.south)
		free(data->map.south);
	if (data->map.west)
		free(data->map.west);
	if (data->map.grid)
		free_double_pointer_size((void **) data->map.grid, data->map.rows);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		if (!init_data(&data, argv[1]))
			return (1);
		render(&data);
		mlx_loop(&data.mlx);
		free_data(&data);
	}
	return (0);
}
