/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:49:56 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 16:56:12 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
