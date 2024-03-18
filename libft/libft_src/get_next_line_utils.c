/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:25:52 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/18 10:51:32 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	got_line(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line(char *s)
{
	char	*line;
	int		nl;
	int		i;

	nl = 0;
	if (!s[0])
		return (0);
	while (s[nl] && s[nl] != '\n')
		nl++;
	line = (char *)ft_calloc(nl + 2, 1);
	if (!line)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] && s[i] == '\n')
		line[i] = '\n';
	return (line);
}
