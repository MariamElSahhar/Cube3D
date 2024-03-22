/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 07:53:07 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/22 10:54:16 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_file_extension(char **args, char *file, t_cub *cub)
{
	if (!ft_strchr(file, '.')
		|| ft_strncmp(".xpm", (file + ft_strlen(file) - 4), 4))
	{
		free(file);
		ft_free_array(args);
		print_error("Texture must be an existing .xpm file", cub);
	}
	return ;
}

static char	*is_valide_texture(char **args, char *iden, t_cub *cub)
{
	char	*path;

	if (is_duplicate(iden, cub))
	{
		ft_free_array(args);
		print_error("Duplicate texture ", cub);
	}
	check_texture_arg(args, cub);
	path = ft_strdup(args[1]);
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = 0;
	check_file_extension(args, path, cub);
	check_texture_file(args, path, cub);
	return (path);
}

void	saving_valide_textures(char *line, t_cub *cub)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[0] && is_valide_id(split[0], "NO", 2))
		cub->game.north = is_valide_texture(split, "NO", cub);
	else if (split[0] && is_valide_id(split[0], "SO", 2))
		cub->game.south = is_valide_texture(split, "SO", cub);
	else if (split[0] && is_valide_id(split[0], "WE", 2))
		cub->game.west = is_valide_texture(split, "WE", cub);
	else if (split[0] && is_valide_id(split[0], "EA", 2))
		cub->game.east = is_valide_texture(split, "EA", cub);
	ft_free_array(split);
	return ;
}

void	is_valide_identifier(char *line, t_cub *cub)
{
	char	**tmp;
	int		len;

	if (check_is_map_begininng(line))
		return ;
	tmp = ft_split(line, ' ');
	len = ft_strlen(tmp[0]);
	if (len && !is_empty(line) && !is_valide_id(tmp[0], "NO", len) && !is_valide_id(tmp[0], "SO", len)
		&& !is_valide_id(tmp[0], "WE", len) && !is_valide_id(tmp[0], "EA", len)
		&& !is_valide_id(tmp[0], "F", len) && !is_valide_id(tmp[0], "C", len)
		&& !is_valide_id(tmp[0], "\n", len))
	{
		ft_free_array(tmp);
		print_error("Invalid identifier", cub);
	}
	// if (len)
	ft_free_array(tmp);
	return ;
}

void	parse_map_components(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->game.file.file_2d && cub->game.file.file_2d[i])
	{
		is_valide_identifier(cub->game.file.file_2d[i], cub);
		saving_valide_textures(cub->game.file.file_2d[i], cub);
		saving_parsing_colors(cub->game.file.file_2d[i], cub);
		saving_validate_map(cub->game.file.file_2d[i], i, cub);
		i++;
	}
	check_missing(cub);
	get_map_width(cub);
	return ;
}
