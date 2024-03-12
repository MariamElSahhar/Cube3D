/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:34:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/12 20:06:35 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render(t_cub *data)
{
	printf("render\n");
	if (data->mlx.img != 0)
	{
		printf("destroy\n");
		mlx_destroy_image(&data->mlx.mlx, data->mlx.img);
	}
	mlx_clear_window(&data->mlx.mlx, data->mlx.mlx_win);
	data->mlx.img = mlx_new_image(&data->mlx, DIM_W, DIM_H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&(data->mlx.bits_per_pixel),
			&(data->mlx.line_length),
			&(data->mlx.endian));
	put_map(data, &data->game.map, &data->player);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
}

/*
void	print_grid(t_map *map, t_game *game)
{
	printf("--printing grid--\n");
	int	i;
	int	j;

	printf("NO %s\n", game->north);
	printf("SO %s\n", game->south);
	printf("EA %s\n", game->east);
	printf("WE %s\n", game->west);
	printf("F = %x, C = %x\n", game->floor, game->ceiling);
	printf("Player facing %c, at (%i,%i)\n",
		map->player_dir, map->player_x, map->player_y);
	i = 0;
	while (i < map->nline)
	{
		j = 0;
		while (j < map->map_width)
			printf("%c", map->map_2d[i][j++]);
		i++;
	}
}
 */
void	parse(int argc, char **argv, t_cub *data)
{
	int	i;

	init_map(data);
	if (argc != 2)
		print_error("Invalid number of arguments", data);
	data->game.file.fd = open(argv[1], O_DIRECTORY);
	if (data->game.file.fd > 0)
		print_error("Argument cannot be a directory", data);
	data->game.file.fd = open(argv[1], O_RDONLY);
	is_args_valide(argv[1], data);
	saving_map_file(data);
	parse_map_components(data);
	i = 0;
	while (data->game.map.map_2d[i])
		i++;
	data->game.map.nline = i;
}

int	destroy_cub(t_cub *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	free(data->mlx.mlx);
	free_cube_map(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cub	data;

	parse(argc, argv, &data);
	if (!init_mlx(&data))
		print_error("Error allocating memory", &data);
	// print_grid(&data.game.map, &data.game);
	render(&data);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &key_down, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0, &destroy_cub, &data);
	mlx_loop(&data.mlx);
	free_cube_map(&data);
	close (data.game.file.fd);
	return (0);
}
