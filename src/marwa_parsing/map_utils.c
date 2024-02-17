/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:27:58 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/12 11:47:54 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//Alloc for len and fill the string with char c
char	*ft_fill_map(int len, char c)
{
	char	*result;

	result = malloc(sizeof(char) * len + 2);
	if (!result)
		return (NULL);
	result[len + 1] = '\0';
	while (len >= 0)
	{
		result[len] = c;
		len--;
	}
	return (result);
}
//Validate line countains only characters in a map.
//" 1, 0, S, W, E, N"
int	check_valid_mapline(char *str, int i, int start)
{
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
			return (-1);
		start = 1;
		i++;
	}
	if (start == 0 && str[i] != '\0')
		return (-1);
	return (0);
}

//Check if a line start with an invalid identifier (!= 1, 0, N, S, W, E, F or C)
bool	is_valid_content(char **value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (determine_line_type(value[i]) == 4)
		{
			printf("Error\nInvalid entry Map\n");
			return (false);
		}
		else
			i++;
	}
	return (true);
}

//Copy map line and add spaces to fill the map up to the len 
//of the longest string
char	*copy_line_dup(const char *str, size_t len)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = ft_fill_map(len, '-');
	if (!cpy)
		return (0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		cpy[i] = str[i];
		i++;
	}
	return (cpy);
}

//Return the len of the longest string in the map.
int	get_mapwidth(char **map, int i, int depth)
{
	int	save_len;
	int	len;

	save_len = 0;
	while (i <= depth)
	{
		len = ft_strlen(map[i]);
		if (len > save_len)
			save_len = len;
		i++;
	}
	return (save_len);
}
