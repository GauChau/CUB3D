/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:52:44 by gchauvot          #+#    #+#             */
/*   Updated: 2025/01/23 11:59:18 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_str_dig(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	rgb_to_int(char *r, char *g, char *b)
{
	int	res;

	if (ft_is_str_dig(r) || ft_is_str_dig(g) || ft_is_str_dig(b))
		return (-2);
	if (ft_atoi(r) > 255 || ft_atoi(g) > 255 || ft_atoi(b) > 255)
		return (printf("wrong color, number between 0 and 255 only\n"), -2);
	res = ft_atoi(r);
	res = (res << 8) | ft_atoi(g);
	res = (res << 8) | ft_atoi(b);
	return (res);
}

int	fl_cl_filler(char **line_split, int *color)
{
	char	**trimed;

	trimed = ft_split(line_split[1], ',');
	if (!trimed)
		return (2);
	if (!trimed[0] || !trimed[1] || !trimed[2] || trimed[3])
		return (ft_free_tab(trimed), write(2, "wrong floor color\n", 18), 2);
	*color = rgb_to_int(trimed[0], trimed[1], trimed[2]);
	if (*color == -2)
		return (ft_free_tab(trimed), write(2, "wrong floor color\n", 18), 2);
	ft_free_tab(trimed);
	return (0);
}

int	fl_cl_parser(char *line, t_mapdata *mapdata)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (!line_split)
		return (2);
	if (!line_split[1])
		return (ft_free_tab(line_split),
			write(2, "no data on floor/ceiling color line\n", 37), 2);
	if (line_split[2] != 0)
		return (ft_free_tab(line_split),
			write(2, "too much info on floor/ceiling color line\n", 42), 2);
	if (!ft_strcmp(line_split[0], "F") && mapdata->floor == -1)
	{
		if (!fl_cl_filler(line_split, &mapdata->floor))
			return (ft_free_tab(line_split), 0);
	}
	else if (!ft_strcmp(line_split[0], "C") && mapdata->ceiling == -1)
	{
		if (!fl_cl_filler(line_split, &mapdata->ceiling))
			return (ft_free_tab(line_split), 0);
	}
	return (ft_free_tab(line_split),
		printf("clparser error, line: @%s@\n", line), 2);
}
