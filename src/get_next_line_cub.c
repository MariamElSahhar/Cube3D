/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:18:24 by marmoham          #+#    #+#             */
/*   Updated: 2024/02/22 10:28:00 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_the_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[i])
		return (0);
	while (str[i] != '\n' && str[i])
		i++;
	line = (char *) malloc (i + 2);
	while (j <= i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*get_the_remainder(char *str)
{
	char	*rem;
	int		i;

	i = 0;
	rem = 0;
	if (!str)
	{
		free (str);
		return (0);
	}
	while (str[i] != '\n' && str[i])
		i++;
	if (gnl_strchr(str, '\n'))
		rem = gnl_strdup(str + i + 1);
	free (str);
	return (rem);
}

static char	*reading(int fd, char *str)
{
	char	*buff;
	int		rd;

	rd = 1;
	buff = 0;
	while ((gnl_strchr(str, '\n') == 0 && rd > 0))
	{
		buff = (char *)malloc(BUFFER_SIZE + 1);
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free (buff);
			return (0);
		}
		buff[rd] = '\0';
		str = gnl_strjoin(str, buff);
		free (buff);
	}
	return (str);
}

char	*get_next_line_cube(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	str = reading(fd, str);
	if (!str)
		return (0);
	line = get_the_line(str);
	str = get_the_remainder(str);
	return (line);
}
// static char	*ft_join_next(char *buffer)
// {
// 	int		i;
// 	int		j;
// 	char	*rest_text;

// 	i = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
// 	if (!buffer[i])
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	if (ft_strlen(buffer) - i >= 1)
// 		return (free(buffer), NULL);
// 	rest_text = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
// 	i++;
// 	j = 0;
// 	while (buffer[i])
// 		rest_text[j++] = buffer[i++];
// 	free(buffer);
// 	return (rest_text);
// }

// static char	*ft_line(char *buffer)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	if (!buffer[i])
// 		return (NULL);
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
// 	line = ft_calloc(i + 2, sizeof(char));
// 	i = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 	{
// 		line[i] = buffer[i];
// 		i++;
// 	}
// 	if (buffer[i] && buffer[i] == '\n')
// 		line[i++] = '\n';
// 	return (line);
// }

// static char	*read_file(int fd, char *result)
// {
// 	char	*buffer;
// 	int		byte_read;

// 	if (!result)
// 		result = ft_calloc(1, 1);
// 	buffer = malloc((long)BUFFER_SIZE + 1);
// 	if (!buffer)
// 		return (NULL);
// 	byte_read = 1;
// 	while (byte_read != 0)
// 	{
// 		byte_read = read(fd, buffer, BUFFER_SIZE);
// 		if (byte_read == -1)
// 		{
// 			free (result);
// 			free (buffer);
// 			return (NULL);
// 		}
// 		buffer[byte_read] = '\0';
// 		result = ft_strjoin(result, buffer);
// 		if (ft_strchr(buffer, '\n'))
// 			break ;
// 	}
// 	free(buffer);
// 	return (result);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*buffer;
// 	char		*read_line;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
// 		return (NULL);
// 	buffer = read_file(fd, buffer);
// 	if (!buffer)
// 		return (NULL);
// 	read_line = ft_line(buffer);
// 	buffer = ft_join_next(buffer);
// 	return (read_line);
// }
// /*int main()
/*{
     int fd1 = open("Marwa.txt", O_RDONLY);
	// static char *buffer;
	// char *res =read_file(fd1,buffer);
	// printf("%s",res);
	char *line;
    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
	 close(fd1);
     return 0;
}*/
