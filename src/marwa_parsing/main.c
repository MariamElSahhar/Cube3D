/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:49:56 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/16 20:40:11 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map_data)
{
	map_data->map = NULL;
	map_data->texture = NULL;
	map_data->floor = NULL;
	map_data->ceilling = NULL;
}

int	main(int argc, char **argv)
{
	t_map	*map_data;

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
	map_data = malloc(sizeof(t_map));
	init_map(map_data);
	if (parsing_main_map(argv, map_data) == false)
		return (1);
	free_map(map_data);
	return (0);
}