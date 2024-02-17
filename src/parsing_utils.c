/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:27:30 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/17 17:20:44 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_size(char **tab)
{
	int	size;

	size = 0;
    if (tab)
	    while (tab[size])
		    size++;
	return (size);
}

// int	check_empty_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v'
// 			&& line[i] != '\f' && line[i] != '\r' && line[i] != '\n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

char	*ft_trim_string(char *str, char c)
{
	char	*new_str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != c)
			len++;
		i++;
	}
	new_str = ft_calloc(sizeof(char), len + 1);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			new_str[len] = str[i];
			len++;
		}
		i++;
	}
	return (new_str);
}

int	check_valid_file(int fd)
{
	char	buf;

	if (read(fd, &buf, 0) == -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	read_nbline_file(int fd)
{
	int		counter;
	char	buf;
	int		res;

	res = 1;
	counter = 0;
	if (check_valid_file(fd) == 1)
		return (-1);
	while (res > 0)
	{
		res = read(fd, &buf, 1);
		if (res == 0)
			break ;
		if (res < 0)
		{
			close(fd);
			return (-1);
		}
		if (buf == '\n')
			counter++;
	}
	close (fd);
	return (counter + 1);
}

int	count_nbline_file(char *file)
{
	int	fd;
	int	nb_line;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (-1);
	nb_line = read_nbline_file(fd);
	return (nb_line);
}
//Tell if a line contains info about map / pos or color.
//0 for empty line, 1 for map, 2 for pos, 3 for color and 4 for anything else.
int	determine_line_type(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '1' || str[i] == '0')
		return (1);
	if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'
		|| str[i] == 'E')
		return (2);
	if (str[i] == 'F' || str[i] == 'C')
		return (3);
	else
		return (4);
}

bool	check_valid_tile(char c)
{
	if (c == '\0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'W' || c == 'E' || c == 'F'
		|| c == 'C' || c == '0' || c == ' ')
		return (true);
	else
		return (false);
}
