/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:27:30 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/27 13:03:05 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_wall(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			free(line);
			return (1);
		}
		i++;
	}
	return (0);
}

void	check_is_2_commas(char *line, t_cub *cub)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == ',')
			n++;
		i++;
	}
	if (n != 2)
	{
		free(line);
		print_error("Invalid color commas", cub);
	}
	return ;
}

void	is_args_valide(char *av, t_cub *cub)
{
	if (!ft_strchr(av, '.') || ft_strncmp(".cub", (av + ft_strlen(av) - 4), 4)
		|| cub->game.file.fd < 0)
		print_error("Invalide file extention", cub);
	return ;
}

int	my_atoi(char *str)
{
	int		i;
	int		res;
	char	*trim;

	i = 0;
	res = 0;
	trim = new_strtrimchar(str, ' ');
	if (!trim || !trim[i])
		return (-1);
	while (trim[i])
	{
		res = (trim[i] - '0') + (res * 10);
		if (res > 255 || !ft_isdigit(trim[i]))
		{
			free(trim);
			return (-1);
		}
		i++;
	}
	free(trim);
	return (res);
}

void	check_missing(t_cub *cub)
{
	if (!cub->game.north || !cub->game.south || !cub->game.west
		|| !cub->game.east)
		print_error("Texture not found", cub);
	if (cub->game.floor == -1 || cub->game.ceiling == -1)
		print_error("Color not found", cub);
	if (!cub->game.map.map_2d)
		print_error("Map not found", cub);
	if (!cub->game.map.player_dir)
		print_error("Player not found", cub);
}
