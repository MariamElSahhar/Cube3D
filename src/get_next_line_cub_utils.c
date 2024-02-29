/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cub_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:30:50 by marmoham          #+#    #+#             */
/*   Updated: 2024/02/28 21:32:46 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*joint;

	i = 0;
	j = 0;
	if (s1 == 0)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (s2 == 0)
		return (0);
	joint = (char *)malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (joint == 0)
		return (0);
	while (s1[i])
		joint[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joint[j++] = s2[i++];
	joint[j] = '\0';
	free(s1);
	return (joint);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	*dest;

	i = 0;
	if (!s)
		return (0);
	dest = (unsigned char *)s;
	while (dest[i])
	{
		if (dest[i] == (unsigned char )c)
			return (&((char *)dest)[i]);
		i++;
	}
	if (c == '\0')
		return (&((char *)dest)[i]);
	return (0);
}

char	*gnl_strdup(char *s1)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	dest = (char *)malloc(i + 1);
	i = 0;
	if (dest == 0)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
// void	gnl_free(char **save)
// {
// 	if (save == 0)
// 		return ;
// 	if (*save)
// 		free(*save);
// 	*save = 0;
// }
/*
size_t	ft_strlen(const char *str)

{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)

{
	while (*s != (unsigned char)c)
	{
		if (*s == '\0')
		{
			return (NULL);
		}
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	if (!s1)
	{
		s1 = malloc (1);
		s1[0] = '\0';
	}
	res = malloc(sizeof(char) * (sizetotal + 1));
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		res[i++] = s2[j++];
	res[sizetotal] = '\0';
	free (s1);
	return (res);
}

void	*ft_calloc(size_t count, size_t size)

{
	char	*memory;
	size_t	i;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	memory = malloc(count * size);
	if (!memory)
		return (NULL);
	while (i < (count * size))
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}
 */
