/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:27:28 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/18 14:44:20 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*copy_and_trim(char *line)
{
	char	*dup;
	char	*trim;

	dup = ft_strdup(line);
	if (dup[ft_strlen(dup) - 1] == '\n')
		dup[ft_strlen(dup) - 1] = 0;
	if (!dup[0])
	{
		free (dup);
		return (NULL);
	}
	trim = new_strtrimchar(dup, ' ');
	free(dup);
	if (!trim)
	{
		free(trim);
		return (NULL);
	}
	return (trim);
}

bool	check_is_map_begininng(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = copy_and_trim(line);
	if (!tmp)
	{
		free(tmp);
		return (false);
	}
	while (tmp[i])
	{
		if (tmp[i] != '1' && tmp[i] != ' ' && tmp[i] != '0' && tmp[i] != 'N'
			&& tmp[i] != 'S' && tmp[i] != 'W' && tmp[i] != 'E')
		{
			free(tmp);
			return (false);
		}
		i++;
	}
	free(tmp);
	return (true);
}

char	**create_2darray_dup(char **array, int start, int nline)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (nline + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < nline)
		copy[i++] = ft_strdup(array[start++]);
	copy[i] = 0;
	return (copy);
}

int	get_map_len(char **arrays)
{
	int	i;

	if (!arrays)
		return (0);
	i = 0;
	while (arrays && arrays[i])
		i++;
	return (i);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) || str[i] == '\n' || str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_map_end(char **file, int start, int end)
{
	while (end > start)
	{
		if (is_empty(file[end - 1]))
			end --;
		else
			return (end);
	}
	return (end);
}

void	saving_validate_map(char *line, int index, t_cub *cub)
{
	int	map_end;

	if (!check_is_map_begininng(line) && cub->game.map.map_pos == -1)
		return ;
	if (cub->game.map.map_pos != -1)
		return ;
	if (cub->game.map.map_pos == -1)
	{
		cub->game.map.map_pos = index;
		map_end = check_map_end(cub->game.file.file_2d, index, cub->game.file.nline);
		cub->game.map.map_2d = create_2darray_dup(cub->game.file.file_2d, index,
				(map_end - index));
	}
	cub->game.map.nline = get_map_len(cub->game.map.map_2d);
	check_map(cub);
	return ;
}
