/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:50:12 by gchauvot          #+#    #+#             */
/*   Updated: 2025/01/20 12:17:31 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	info_parser(char *line, t_mapdata *mapdata)
{
	char	**line_split;

	if (!line)
		return (2);
	line_split = ft_split(line, ' ');
	if (line_split && line_split[0]
		&& ft_char_in_set(line_split[0][0], "NWES"))
	{
		if (texture_files_parser(line_split, mapdata))
			return (ft_free_tab(line_split), 2);
	}
	else if (line_split && line_split[0]
		&& ft_char_in_set(line_split[0][0], "FC"))
	{
		if (fl_cl_parser(line, mapdata))
			return (ft_free_tab(line_split), 2);
	}
	else
		return (printf("Wrong data ID on line: %s\n", line),
			ft_free_tab(line_split), 2);
	return (ft_free_tab(line_split), 0);
}

int	datamapcheck(t_mapdata *mapdata)
{
	if (!mapdata->north || !mapdata->south || !mapdata->west
		|| !mapdata->east || mapdata->ceiling == -1 || mapdata->floor == -1)
	{
		return (0);
	}
	return (2);
}

int	texture_files_parser(char **line_split, t_mapdata *mapdata)
{
	int	axess;

	if (!line_split)
		return (2);
	if (line_split[2] != NULL)
		return (write(2, "too much info on texture path line\n", 35), 2);
	if (ft_strcmp(ft_strrchr(line_split[1], '.'), ".xpm"))
		return (printf("error, .xpm file needed\n"), 2);
	axess = access(line_split[1], F_OK);
	if (axess != 0)
		return (printf("access return: %d\n", axess),
			perror("access file error"), 2);
	if (!ft_strcmp(line_split[0], "NO") && mapdata->north == NULL)
		mapdata->north = ft_strdup(line_split[1]);
	else if (!ft_strcmp(line_split[0], "SO") && !mapdata->south)
		mapdata->south = ft_strdup(line_split[1]);
	else if (!ft_strcmp(line_split[0], "EA") && !mapdata->east)
		mapdata->east = ft_strdup(line_split[1]);
	else if (!ft_strcmp(line_split[0], "WE") && !mapdata->west)
		mapdata->west = ft_strdup(line_split[1]);
	else if (line_split[0][0] != '\n')
		return (printf("wrong data ID or data ID duplicates\n"), 2);
	return (0);
}
