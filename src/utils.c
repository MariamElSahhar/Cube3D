/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:39:01 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/22 12:39:25 by melsahha         ###   ########.fr       */
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
