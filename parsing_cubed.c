/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cubed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:59:22 by gautierchau       #+#    #+#             */
/*   Updated: 2025/01/17 14:24:59 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	open_cube_file(char *filename, t_mapdata *mapdata)
{
	int	file_fd;

	mapdata->start_pos[0] = -1;
	mapdata->ceiling = -1;
	mapdata->floor = -1;
	mapdata->mapheight = 0;
	file_fd = open(filename, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		perror("cub3d: ");
		return (-1);
	}
	else
	{
		if (reader(filename, file_fd, mapdata) != 0)
			return (close(file_fd), 2);
	}
	return (close(file_fd), 0);
}

int	reader(char *filename, int file_fd, t_mapdata *mapdata)
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
		if (datamapcheck(mapdata, &mapbool, line) == 0)
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
			free (mapdata->east);
		if (mapdata->north)
			free (mapdata->north);
		if (mapdata->south)
			free (mapdata->south);
		if (mapdata->west)
			free (mapdata->west);
		free(mapdata);
	}
	return (0);
}

int	cub_parser(int argc, char **argv)
{
	t_mapdata	*mapdata;

	if (argc != 2)
		return (printf("not enough args\n"), 2);
	if (ft_strcmp(".cub", ft_strrchr(argv[1], '.')))
		return (write(2, "wrong filetype, .cub needed\n", 28), 2);
	mapdata = ft_calloc(1, sizeof(t_mapdata));
	if (!mapdata)
		return (2);
	if (open_cube_file(argv[1], mapdata))
		return (freemapdata(mapdata), printf("opencubfile error detected\n"), 0);
	if (map_validity_checker(mapdata))
		return (freemapdata(mapdata),
			printf("map validity error detected\n"), 0);
	freemapdata(mapdata);
}

int	main(int argc, char **argv, char **env)
{
	cub_parser(argc, argv);
	return (0);
}
