/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:54:47 by gchauvot          #+#    #+#             */
/*   Updated: 2025/01/24 18:02:49 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_filler(int column, char *line, t_mapdata *mapdata)
{
	int	i;

	i = 0;
	if (!line || ft_strlen(line) > 255)
		return (2);
	if (ft_strchr(line, '\n'))
		ft_strchr(line, '\n')[0] = 0;
	while (line[i])
	{
		if (!ft_char_in_set(line[i], " 01NSEW$P\n"))
			return (printf("Invalid character in map design section\n"), 2);
		else if (ft_char_in_set(line[i], "NSEW") && mapdata->start_pos[0] != -1)
			return (printf("starter pos duplicate\n"), 2);
		else if (ft_char_in_set(line[i], "NSEW"))
		{
			mapdata->facing = line[i];
			mapdata->start_pos[0] = i;
			mapdata->start_pos[1] = column;
		}
		mapdata->map_matrix[column][i] = line[i];
		i++;
	}
	if (i > mapdata->width)
		mapdata->width = i ;
	return (0);
}

int	cross_checker(t_mapdata *mapdata, int x, int y)
{
	if (mapdata->map_matrix[y][x] == '0'
		|| ft_char_in_set(mapdata->map_matrix[y][x], "NSEW$"))
	{
		if (y == 0 || x == 0 || y == mapdata->height
			|| x == mapdata->width)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y - 1][x] == ' '
			|| mapdata->map_matrix[y - 1][x] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y + 1][x] == ' '
			|| mapdata->map_matrix[y + 1][x] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y][x - 1] == ' '
			|| mapdata->map_matrix[y][x -1] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y][x + 1] == ' '
			|| mapdata->map_matrix[y][x + 1] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
	}
	return (0);
}

int	datamapcheck2(t_mapdata *mapdata, bool *mapbool, char *line)
{
	if (mapdata->north && mapdata->south && mapdata->west
		&& mapdata->east && mapdata->ceiling != -1 && mapdata->floor != -1)
	{
		*mapbool = 1;
		if (line[0] == '\n')
			return (printf("Empty line on map section forbidden\n"), 3);
		else if (map_filler(mapdata->height, line, mapdata) == 2)
			return (3);
		mapdata->height++;
	}
	return (0);
}

int	map_validity_checker(t_mapdata *mapdata)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (mapdata->start_pos[0] == -1 || mapdata->start_pos[1] == -1)
		return (printf("Invalid map: #NO START\n"), 2);
	while (y < mapdata->width)
	{
		x = 0;
		while (x < mapdata->width)
		{
			if (cross_checker(mapdata, x, y) != 0)
				return (2);
			x++;
		}
		y++;
	}
	return (printf("Valid map: #00\n"), 0);
}
