/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:36:06 by marwamostaf       #+#    #+#             */
/*   Updated: 2024/03/22 10:51:37 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	saving_clr_content(char *line, char *content, char **color, t_cub *cub)
{
	int	res;

	res = my_atoi(content);
	if (res < 0)
	{
		free(line);
		ft_free_array(color);
		print_error("Invalid color numbers", cub);
	}
	return (res);
}

int	create_rgb_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	check_color_args(char *line, t_cub *cub)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	line[0] = ' ';
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	split = ft_split(line, ',');
	if (!split[1] || !split[2])
	{
		free(line);
		ft_free_array(split);
		print_error("Invalid color args", cub);
	}
	r = saving_clr_content(line, split[0], split, cub);
	g = saving_clr_content(line, split[1], split, cub);
	b = saving_clr_content(line, split[2], split, cub);
	ft_free_array(split);
	return (create_rgb_color(r, g, b));
}

int	checking_color(char *line, char *iden, t_cub *cub)
{
	if (is_duplicate(iden, cub))
	{
		free(line);
		print_error("Duplicate color", cub);
	}
	check_is_2_commas(line, cub);
	return (check_color_args(line, cub));
}

void	saving_parsing_colors(char *line, t_cub *cub)
{
	char	*res;

	res = new_strtrimchar(line, ' ');
	if (!res || !res[0] || !res[1])
		return ;
	if (res[0] == 'F' && res[1] == ' ')
		cub->game.floor = checking_color(res, "F", cub);
	else if (res[0] == 'C' && res[1] == ' ')
		cub->game.ceiling = checking_color(res, "C", cub);
	else if ((res[0] == 'F' && res[1] != ' ')
		|| (res[0] == 'C' && res[1] != ' '))
	{
		free(res);
		print_error("Invalid color ", cub);
	}
	free(res);
	return ;
}
