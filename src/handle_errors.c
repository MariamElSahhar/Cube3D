/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:55:09 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 17:04:57 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_array(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i] != NULL)
				free(tab[i]);
			i++;
		}
		free (tab);
	}
	return ;
}


bool	free_color(char **color)
{
	ft_free_array(color);
	printf("Invalid Color\n");
	return (false);
}

bool	print_msg(char *msg, int fd)
{
	ft_putstr_fd(msg, fd);
	return (false);
}

void	free_map(t_map *map_data)
{
	if (map_data->map)
		ft_free_array(map_data->map);
	if (map_data->texture)
		ft_free_array(map_data->texture);
	if (map_data->floor)
		free(map_data->floor);
	if (map_data->ceiling)
		free(map_data->ceiling);
	// free(map_data);
}
