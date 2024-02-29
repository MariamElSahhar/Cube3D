/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:09:53 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/28 21:33:27 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_valide_id(char *iden, char *cmp, int len)
{
	int	res;

	res = ft_strlen(cmp);
	if (res != len)
		return (false);
	if (!ft_strncmp(iden, cmp, len))
		return (true);
	return (false);
}

bool	is_whitespace(int c)
{
	if (c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (true);
	return (false);
}

void	check_texture_file(char **args, char *path, t_cub *cub)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		free(path);
		ft_free_array(args);
		print_error("Texture cannot be a directory", cub);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_free_array(args);
		print_error("Texture file edoes not exist", cub);
	}
	close (fd);
	return ;
}

bool	is_duplicate(char *iden, t_cub *cub)
{
	if ((is_valide_id(iden, "NO", 2) && cub->game.north)
		|| (is_valide_id(iden, "SO", 2) && cub->game.south)
		|| (is_valide_id(iden, "WE", 2) && cub->game.west)
		|| (is_valide_id(iden, "EA", 2) && cub->game.east)
		|| (is_valide_id(iden, "F", 1) && cub->game.floor != -1)
		|| (is_valide_id(iden, "C", 1) && cub->game.ceiling != -1))
		return (true);
	return (false);
}

void	check_texture_arg(char **arg, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (arg[2] && arg[2][0] != '\n')
	{
		ft_free_array(arg);
		print_error("Invalid texture ", cub);
	}
	while (arg && arg[i])
	{
		if (is_whitespace(arg[i][j]))
		{
			ft_free_array(arg);
			print_error("Invalid white space", cub);
		}
		j++;
		if (!arg[i][j])
		{
			j = 0;
			i++;
		}
	}
	return ;
}
