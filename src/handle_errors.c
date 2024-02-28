/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:55:09 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/27 11:03:53 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
	return ;
}

void	free_cube_map(t_cub *cub)
{
	ft_free_array(cub->game.file.file_2d);
	ft_free_array(cub->game.map.map_2d);
	if (cub->game.file.line)
		free(cub->game.file.line);
	if (cub->game.north)
		free(cub->game.north);
	if (cub->game.south)
		free(cub->game.south);
	if (cub->game.west)
		free(cub->game.west);
	if (cub->game.east)
		free(cub->game.east);
}

void	print_error(char *msg, t_cub *cub)
{
	printf("Error\n");
	printf("%s\n", msg);
	if (cub->game.file.fd > 0)
		close(cub->game.file.fd);
	free_cube_map(cub);
	exit (1);
}
