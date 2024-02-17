/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:23:47 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/15 20:44:50 by melsahha         ###   ########.fr       */
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

	i = 0;
	printf("freeing double pointer: ");
	while (i < size)
	{
		printf("%i ", i);
		free(ptr[i]);
		i++;
	}
	printf(" | ");
	free(ptr);
	printf(" |\n");
}
