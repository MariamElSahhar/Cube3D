/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:12:29 by melsahha          #+#    #+#             */
/*   Updated: 2024/02/21 15:11:34 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_checkset(const char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	index;

	index = 0;
	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_checkset(s1[start], set) == 1)
		start++;
	while (end > start && ft_checkset(s1[end - 1], set) == 1)
		end--;
	str = malloc(sizeof(*s1) * (end - start) + 1);
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[index] = s1[start];
		start++;
		index++;
	}
	str[index] = '\0';
	return (str);
}
// int	isin(char s, const char *c)
// {
// 	int		i;
// 	int		size;

// 	size = ft_strlen(c);
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (s == c[i])
// 			return (1);
// 		i ++;
// 	}
// 	return (0);
// }

// size_t	count_trims(char const *s1, char const *set)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	count;
// 	char	*p;

// 	if (!ft_strlen(set) || !ft_strlen(s1))
// 		return (0);
// 	i = 0;
// 	j = ft_strlen(s1) - 1;
// 	p = (char *) s1;
// 	while (i <= j && isin(p[i], set))
// 		i++;
// 	count = i;
// 	while (i <= j && isin(p[j], set))
// 	{
// 		count++;
// 		j--;
// 	}
// 	return (count);
// }

// int	get_stop(char *p, char *set)
// {
// 	int	i;

// 	i = ft_strlen(p) - 1;
// 	while (i >= 0 && isin(p[i], set))
// 		i--;
// 	return (i);
// }

// void	init_ret(char *ret, char *p, char *set, int stop)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < stop && isin(p[i], set))
// 		i++;
// 	while (i <= stop)
// 	{
// 		ret[j] = p[i];
// 		i++;
// 		j++;
// 	}
// 	ret[j] = '\0';
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	char	*p;
// 	char	*ret;
// 	int		stop;
// 	size_t	size;

// 	p = (char *) s1;
// 	size = ft_strlen(p) - count_trims(p, set);
// 	ret = (char *)malloc(size + 1);
// 	if (!ret || !p)
// 		return (0);
// 	stop = get_stop(p, (char *)set);
// 	init_ret(ret, p, (char *)set, stop);
// 	return (ret);
// }

/* int	main(void)
{
	printf("%s\n", ft_strtrim("", "acb"));
	printf("%s\n", ft_strtrim("abc", ""));
	printf("%s\n", ft_strtrim("", ""));
	return (0);
}
 */
