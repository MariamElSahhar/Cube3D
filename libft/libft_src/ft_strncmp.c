/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmoham <marmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:57:08 by melsahha          #+#    #+#             */
/*   Updated: 2024/03/18 10:48:38 by marmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	if (s1[i] && !s2[i] && i < n)
		return ((unsigned char)s1[i]);
	if (s2[i] && !s1[i] && i < n)
		return (0 - (unsigned char)s2[i]);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1))
		|| ft_strncmp(s1, s2, ft_strlen(s2)));
}

/* #include <stdio.h>
#include <string.h>
int main()
{
	char *a = "\200";
	char *b = "\20";
	printf("%d\n",ft_strncmp(a, b, 5));
	printf("%d\n",strncmp(a, b, 5));
	return 0;
} */
