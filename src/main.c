/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:34:48 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/13 19:34:50 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render(t_cub *data)
{
	if (data->mlx.img != 0)
		mlx_destroy_image(&data->mlx.mlx, data->mlx.img);
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
	close (data->game.file.fd);
}

int	destroy_cub(t_cub *data)
{
	printf("destroying\n");

	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->game.textures[i].img != 0)
			mlx_destroy_image(data->mlx.mlx, data->game.textures[i].img);
		if (data->game.textures[i].path)
			free(data->game.textures[i].path);
		i++;
	}
	printf("done destroying\n");
	if (data->mlx.mlx && data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.mlx && data->mlx.mlx_win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	if (data->mlx.mlx)
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
	render(&data);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &key_down, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0, &destroy_cub, &data);
	mlx_loop(&data.mlx);
	free_cube_map(&data);
	return (0);
}
