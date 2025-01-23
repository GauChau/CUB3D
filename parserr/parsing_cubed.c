/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cubed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:59:22 by gautierchau       #+#    #+#             */
/*   Updated: 2025/01/23 12:18:49 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_cube_file(char *filename, t_mapdata *mapdata)
{
	int	file_fd;

	mapdata->start_pos[0] = -1;
	mapdata->ceiling = -1;
	mapdata->floor = -1;
	mapdata->height = 0;
	file_fd = open(filename, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		perror("cub3d: ");
		return (-1);
	}
	else
	{
		if (reader(file_fd, mapdata) != 0)
			return (close(file_fd), 2);
	}
	return (close(file_fd), 0);
}

int	reader(int file_fd, t_mapdata *mapdata)
{
	char				*line;
	static bool			mapbool;

	while (1)
	{
		line = get_next_line(file_fd);
		if (!line || line[0] == 0)
			break ;
		if (ft_strlen(line) == 1 || (line[0] == '\n' && !mapbool))
		{
			free(line);
			continue ;
		}
		if (ft_strchr(line, '\n') && !mapbool)
			ft_strchr(line, '\n')[0] = 0;
		if (datamapcheck(mapdata) == 0)
		{
			if (info_parser(line, mapdata))
				return (free(line), 2);
		}
		else if (datamapcheck2(mapdata, &mapbool, line) == 3)
			return (free(line), 2);
		free(line);
	}
	return (free(line), 0);
}

int	freemapdata(t_mapdata *mapdata)
{
	if (mapdata)
	{
		if (mapdata->east)
		{
			free (mapdata->east);
			mapdata->east = NULL;
		}
		if (mapdata->north)
		{
			free (mapdata->north);
			mapdata->north = NULL;
		}
		if (mapdata->south)
		{
			free (mapdata->south);
			mapdata->south = NULL;
		}
		if (mapdata->west)
		{
			free (mapdata->west);
		}
		free(mapdata);
		mapdata = NULL;
	}
	return (0);
}

t_mapdata	*cub_parser(int argc, char **argv)
{
	t_mapdata	*mapdata;

	if (argc != 2)
		return (printf("not enough args\n"), NULL);
	if (ft_strcmp(".cub", ft_strrchr(argv[1], '.')))
		return (write(2, "wrong filetype, .cub needed\n", 28), NULL);
	mapdata = ft_calloc(1, sizeof(t_mapdata));
	if (!mapdata)
		return (NULL);
	if (open_cube_file(argv[1], mapdata))
		return (freemapdata(mapdata),
			printf("opencubfile error detected\n"), NULL);
	if (map_validity_checker(mapdata))
		return (freemapdata(mapdata),
			printf("map validity error detected\n"), NULL);
	return (mapdata);
}

// int	main(int argc, char **argv)
// {
// 	cub_parser(argc, argv);
// 	return (0);
// }
