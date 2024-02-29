/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:27:58 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/02/28 21:32:07 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_start(char const *str, int const c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
	{
		i++;
	}
	return (i);
}

static int	is_end(char const *str, int const c, int start, int len)
{
	int	end;

	end = len - 1;
	while (end > start && str[end] == c)
	{
		end--;
	}
	end++;
	return (end);
}

char	*new_strtrimchar(char const *str, int const c)
{
	int		start;
	int		end;
	char	*trim;
	int		i;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	start = is_start(str, c);
	if (start == ft_strlen(str))
		return (NULL);
	end = is_end(str, c, start, ft_strlen(str));
	if (!start && !end)
	{
		trim = ft_strdup(str);
		return (trim);
	}
	trim = (char *)malloc((end - start) + 1);
	if (!trim)
		return (NULL);
	while (start < end)
		trim[i++] = str[start++];
	trim[i] = 0;
	return (trim);
}
