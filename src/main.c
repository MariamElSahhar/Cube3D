/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:34:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/17 17:09:01 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* int	init_data(t_data *data)
{
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
	data->player.pos[0] = (data->map.player_x * TILE) + (TILE / 2);
	data->player.pos[1] = (data->map.player_y * TILE) + (TILE / 2);
	printf("done data init\n");
	return (1);
}
 */
/* void	render(t_data *data)
{
	if (data->mlx.img != 0)
		mlx_destroy_image(&data->mlx, data->mlx.img);
	mlx_clear_window(&data->mlx, data->mlx.mlx_win);
	data->mlx.img = mlx_new_image(&data->mlx, DIM_W, DIM_H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&(data->mlx.bits_per_pixel),
			&(data->mlx.line_length),
			&(data->mlx.endian));
	put_map(data, &data->map, &data->player);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
} */

void	init_map(t_map *map_data)
{
	map_data->map = NULL;
	map_data->texture = NULL;
	map_data->floor = NULL;
	map_data->ceiling = NULL;
}


/*
void	free_data(t_data *data)
{
	printf("freeing data\n");
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
} */
void	print_grid(t_map *map)
{
	int	i;
	int	j;

	printf("NO %s\n", map->texture[0]);
	printf("SO %s\n", map->texture[1]);
	printf("EA %s\n", map->texture[2]);
	printf("WE %s\n", map->texture[3]);
	printf("F %i,%i,%i\n", map->floor[0], map->floor[1], map->floor[2]);
	printf("C %i,%i,%i\n", map->ceiling[0], map->ceiling[1], map->ceiling[2]);
	printf("Dir %c\n", map->orientation);
	i = 0;
	while (i < map->map_width)
	{
		j = 0;
		while (j < map->map_height)
			printf("%c", map->map[i][j]);
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Error\nInvalid number of argument\n");
		return (1);
	}
	if (check_cubfile_extention(argv[1]) == false)
	{
		printf("Error\nInvalid file type\n");
		return (1);
	}
	init_map(&data.map);
	if (parsing_main_map(argv, &data.map) == false)
		return (1);
	// if (!init_data(&data)) {
	// 		free_map(&data.map);
	// 		return (1);
	// }
	// render(&data);
	// mlx_loop(&data.mlx);
	free_map(&data.map);
	return (0);
}
