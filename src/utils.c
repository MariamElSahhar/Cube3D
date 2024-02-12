/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:23:47 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/12 10:24:02 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_double_pointer(void **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
        free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_double_pointer_size(void **ptr, int size)
{
	int	i;

    printf("freeing dbl ptr %i\n", size);
	i = 0;
	while (i < size)
	{
        printf("%i ", i);
        free(ptr[i]);
		i++;
	}
	free(ptr);
    printf("freeing dbl ptr done\n");
}
