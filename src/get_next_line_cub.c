/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:18:24 by marmoham          #+#    #+#             */
/*   Updated: 2024/02/17 16:36:39 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	gnl_nl_chr(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] != '\n')
		return (0);
	return (1);
}

static int	gnl_line(char **save, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*save)[i] != '\n' && (*save)[i] != '\0')
		i++;
	if ((*save)[i] == '\n')
	{
		*line = ft_substr(*save, 0, i);
		temp = ft_strdup(&((*save)[i + 1]));
		free(*save);
		*save = temp;
		if ((*save)[0] == '\0')
			gnl_free(save);
		return (1);
	}
	else
	{
		*line = ft_strdup(*save);
		gnl_free(save);
		return (0);
	}
}

int	gnl_return(char **save, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (!ret && !save[fd])
	{
		*line = ft_strdup("\0");
		return (0);
	}
	return (gnl_line(&save[fd], line));
}

int	gnl_loop(int ret, int fd, char *buf, char **save)
{
	char	*temp;

	ret = read(fd, buf, 0);
	if (ret < 0)
		return (-1);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (!save[fd])
			save[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(save[fd], buf);
			free(save[fd]);
			save[fd] = temp;
		}
		if (gnl_nl_chr(buf))
			break ;
	}
	return (ret);
}

int	get_next_line_cub(int fd, char **line)
{
	static char	*save[1024];
	char		*buf;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	ret = 1;
	ret = gnl_loop(ret, fd, buf, save);
	gnl_free(&buf);
	return (gnl_return(save, line, ret, fd));
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
