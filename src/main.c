/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:34:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/26 10:19:51 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//  int	init_data(t_cub *data)
// {
// 	printf("mlx init\n");
// 	data->mlx.mlx = mlx_init();
// 	printf("mlx new image\n");
// 	data->mlx.img = mlx_new_image(data->mlx.mlx, DIM_W, DIM_H);
// 	printf("mlx get data addr\n");
// 	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
// 			&(data->mlx.bits_per_pixel), &(data->mlx.line_length),
// 			&(data->mlx.endian));
// 	printf("mlx new window\n");
// 	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
// 			DIM_W, DIM_H, "Hello World");
// 	data->player.pos[0] = (data->game.map.player_x * TILE) + (TILE / 2);
// 	data->player.pos[1] = (data->game.map.player_y * TILE) + (TILE / 2);
// 	printf("done data init\n");
// 	return (1);
// }
//  void	render(t_cub *data)
// {
// 	if (data->mlx.img != 0)
// 		mlx_destroy_image(&data->mlx, data->mlx.img);
// 	mlx_clear_window(&data->mlx, data->mlx.mlx_win);
// 	data->mlx.img = mlx_new_image(&data->mlx, DIM_W, DIM_H);
// 	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
// 			&(data->mlx.bits_per_pixel),
// 			&(data->mlx.line_length),
// 			&(data->mlx.endian));
// 	put_map(data, &data->game.map, &data->player);
// 	mlx_put_image_to_window(data->mlx.mlx,
// 		data->mlx.mlx_win, data->mlx.img, 0, 0);
// }

void	init_map(t_cub *map_data)
{
	map_data->game.north = NULL;
	map_data->game.south = NULL;
	map_data->game.west = NULL;
	map_data->game.east = NULL;
	map_data->game.floor = -1;
	map_data->game.ceiling = -1;
	map_data->game.file.fd = 0;
	map_data->game.file.nline = 0;
	map_data->game.file.line = NULL;
	map_data->game.file.file_2d = NULL;
	map_data->game.map.map_2d = NULL;
	map_data->game.map.map_pos = -1;
	map_data->game.map.nline = 0;
	map_data->game.map.player_x = -1;
	map_data->game.map.player_y = -1;
	map_data->game.map.player_dir = 0;
	map_data->game.map.map_width = 0;
	return ;
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
// void	print_grid(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	printf("NO %s\n", map->texture[0]);
// 	printf("SO %s\n", map->texture[1]);
// 	printf("EA %s\n", map->texture[2]);
// 	printf("WE %s\n", map->texture[3]);
// 	printf("F %i,%i,%i\n", map->floor[0], map->floor[1], map->floor[2]);
// 	printf("C %i,%i,%i\n", map->ceiling[0], map->ceiling[1], map->ceiling[2]);
// 	printf("Dir %c\n", map->player_dir);
// 	i = 0;
// 	while (i < map->map_width)
// 	{
// 		j = 0;
// 		while (j < map->map_height)
// 			printf("%c", map->map_2d[i][j]);
// 		printf("\n");
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_cub	cub_data;

	init_map(&cub_data);
	if (argc != 2)
		print_error("Invalid number of arguments", &cub_data);
	cub_data.game.file.fd = open(argv[1], O_DIRECTORY);
	if (cub_data.game.file.fd > 0)
		print_error("Argument cannot be a directory", &cub_data);
	cub_data.game.file.fd = open(argv[1], O_RDONLY);
	is_args_valide(argv[1], &cub_data);
	saving_map_file(&cub_data);
	parse_map_components(&cub_data);
	// if (!init_data(&data)) {
	// 		free_map(&data.map);
	// 		return (1);
	// }
	// render(&data);
	// mlx_loop(&data.mlx);
	free_cube_map(&cub_data);
	close (cub_data.game.file.fd);
	return (0);
}
