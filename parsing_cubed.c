/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cubed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautierchauvot <gautierchauvot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:59:22 by gautierchau       #+#    #+#             */
/*   Updated: 2025/01/16 23:27:12 by gautierchau      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int ft_is_str_dig(char *str)
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

int	texture_files_parser(char **line_split, t_mapdata *mapdata)
{
	int axess;
	
	if (!line_split)
		return (2);
	if (line_split[2] != NULL)
		return(write(2, "too much info on texture path line\n", 35), 2);
	if (ft_strcmp(ft_strrchr(line_split[1], '.'), ".xmp"))
		return (printf("error, .xmp file needed\n"), 2);
	axess = access(line_split[1], F_OK);
	if (axess != 0)
		return (printf("access return: %d\n", axess),perror("access file error"), 2);
	if (!ft_strcmp(line_split[0], "NO") && mapdata->north == NULL)
		mapdata->north = ft_strdup(line_split[1]);
	else if (!ft_strcmp(line_split[0], "SO") && !mapdata->south)
		mapdata->south = ft_strdup(line_split[1]);
	else if (!ft_strcmp(line_split[0], "EA") && !mapdata->east)
		mapdata->east = ft_strdup(line_split[1]);
	else if (!ft_strcmp(line_split[0], "WE") && !mapdata->west)
		mapdata->west = ft_strdup(line_split[1]);
	else if(line_split[0][0] != '\n')
		return(printf("wrong data ID or data ID duplicates\n"), 2);
	return (0);
}

int fl_cl_filler(char **line_split, int *color)
{
	char	**trimed;

	trimed = ft_split(line_split[1], ',');
	if (!trimed)
		return (2);
	if (!trimed[0] || !trimed[1] || !trimed[2] || trimed[3])
		return(ft_free_tab(trimed), write(2, "wrong floor color\n", 18), 2);
	*color = rgb_to_int(trimed[0], trimed[1], trimed[2]);
	if (*color == -2)
		return(ft_free_tab(trimed), write(2, "wrong floor color\n", 18), 2);
	ft_free_tab(trimed);
	return (0);
}

int fl_cl_parser(char *line, t_mapdata *mapdata)
{
	char	**line_split;
	int		i;

	i = 0;
	line_split = ft_split(line, ' ');
	if (!line_split)
		return (2);
	if (line_split[2])
		return(write(2, "too much info on floor/ceiling color line\n", 42), 2);
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
	return (ft_free_tab(line_split), printf("clparser error, line: @%s@\n", line), 2);
}

int	info_parser(char *line, t_mapdata *mapdata)
{
	char	**line_split;

	if (!line)
		return (2);
	if (ft_char_in_set(line[0], "NWES"))
	{
		line_split = ft_split(line, ' ');
		if (texture_files_parser(line_split, mapdata))
			return (ft_free_tab(line_split), 2);
		ft_free_tab(line_split);
	}
	else if (ft_char_in_set(line[0], "FC"))
	{
		if (fl_cl_parser(line, mapdata))
			return (2);
	}
	else
		return (printf("Wrong data ID on line: %s\n", line), 2);
	return (0);
}

int map_filler(int column, char *line, t_mapdata *mapdata)
{
	int	i;

	i = 0;
	if (!line || ft_strlen(line) > 255)
		return (2);
	if (ft_strchr(line, '\n'))
		ft_strchr(line, '\n')[0] = 0;
	while (line[i])
	{
		 printf("start pos: %d, linei[%d]:%c\n", mapdata->start_pos[0], i,line[i]);
		if (!ft_char_in_set(line[i], " 01NSEW\n"))
			return (printf("Invalid character in map design section\n"), 2);
		else if (ft_char_in_set(line[i], "NSEW") && mapdata->start_pos[0] != -1)
			return (printf("starter pos duplicate\n"), printf("FAIL start pos: %d, linei[%d]:%c\n", mapdata->start_pos[0], i,line[i]),2);
		else if (ft_char_in_set(line[i], "NSEW"))
		{
			mapdata->facing = line[i];
			mapdata->start_pos[0] = i;
			mapdata->start_pos[1] = column;
		}
		mapdata->map_matrix[column][i] = line[i];
		i++;
	}
	if (i > mapdata->mapwidth)
		mapdata->mapwidth = i ;
	return (0);
}

int	datamapcheck(t_mapdata *mapdata, bool *mapbool, char *line)
{
	if (!mapdata->north || !mapdata->south || !mapdata->west
		|| !mapdata->east || mapdata->ceiling == -1 || mapdata->floor == -1)
	{
		return (0);
	}
	return (2);
}

int	datamapcheck2(t_mapdata *mapdata, bool *mapbool, char *line)
{
	if (mapdata->north && mapdata->south && mapdata->west
		&& mapdata->east && mapdata->ceiling != -1 && mapdata->floor != -1)
	{
		*mapbool = 1;
		printf("PREFILL: line: %s\n", line);
		if (line[0] == '\n' || map_filler(mapdata->mapheight, line, mapdata) == 2)
			return (3);
		mapdata->mapheight++;
	}
	return (0);
}

int	reader(char *filename, int file_fd, t_mapdata *mapdata)
{
	char			*line;
	bool		mapbool = 0;

	while (1)
	{
		line = get_next_line(file_fd);
		printf("GNL: line: %s\n", line);
		if (!line || line[0] == 0)
			break ;
		if (ft_strlen(line) == 0 || (ft_strlen(line) == 1 && line[0] == '\n' && !mapbool))
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

int open_cube_file(char *filename, t_mapdata *mapdata)
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
			return (close(file_fd),2);
	}
	return (close(file_fd), 0);
}

// int	map_edge_checker(t_mapdata *mapdata)
// {
// 	int	x;
// 	int	y;
// 	int	i;

// 	i = 0;
// 	x = 0;
// 	y = 0;
// 	while (x < mapdata->mapwidth)
// 	{
// 		if (mapdata->map_matrix[0][x] == '0')
// 			return (printf("open map1\n"), 2);
// 		x++;
// 	}
// 	x = 0;
// 	while (x < mapdata->mapwidth)
// 	{
// 		if (mapdata->map_matrix[mapdata->mapheight-1][x] == '0')
// 			return (printf("open map2\n"), 2);
// 		x++;
// 	}
// 	y = 0;
// 	while (y < mapdata->mapheight)
// 	{
// 		if (mapdata->map_matrix[y][0] == '0')
// 			return (printf("open map3\n"), 2);
// 		y++;
// 	}
// 	y = 0;
// 	while (y < mapdata->mapheight)
// 	{
// 		if (mapdata->map_matrix[y][mapdata->mapwidth-1] == '0')
// 			return (printf("open map4\n"), 2);
// 		y++;
// 	}
// 	return (printf("Valid map 5\n"), 0);

// }

int	cross_checker(t_mapdata *mapdata, int x, int y)
{
	if (mapdata->map_matrix[y][x] == '0'
		|| ft_char_in_set(mapdata->map_matrix[y][x], "NSEW"))
	{
		if (y == 0 || x == 0 || y == mapdata->mapheight || x == mapdata->mapwidth)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y - 1][x] == ' ' || mapdata->map_matrix[y - 1][x] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y + 1][x] == ' '|| mapdata->map_matrix[y + 1][x] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y][x - 1] == ' '|| mapdata->map_matrix[y][x -1] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
		if (mapdata->map_matrix[y][x + 1] == ' '|| mapdata->map_matrix[y][x + 1] == 0)
			return (printf("Invalid map on (x,y): (%d,%d)\n", x, y), 2);
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
	while (y < mapdata->mapwidth)
	{
		x = 0;
		while (x < mapdata->mapwidth)
		{
			if (cross_checker(mapdata, x, y) != 0)
				return (2);
			x++;
		}
		y++;
	}
	return (printf("Valid map: #00\n"), 0);
}

int main(int argc, char **argv, char **env)
{
	t_mapdata	*mapdata;

	if (argc != 2)
		return (printf("not enough args\n"),2);
	//check si le fichier est bien .cub en cherchant le . dans la string et regardant a partir de la si juste .cub
	if (ft_strcmp(".cub", ft_strrchr(argv[1], '.')))
		return (write(2,"wrong filetype, .cub needed\n", 28), 2);
	//open le .cub
	mapdata = ft_calloc(1, sizeof(t_mapdata));
	if (!mapdata)
		return(2);
	
	if (open_cube_file(argv[1], mapdata))
		return (printf("opencubfile error detected\n"), 0);
	// if (map_edge_checker(mapdata))
	// 	return (printf("edge checker error detected\n"),0);
	if (map_validity_checker(mapdata))
		return(printf("map validity error detected\n"),0);
	printf("floor: %d\n", mapdata->floor);
	printf("ceiling: %d\n", mapdata->ceiling);
	printf("mapheight: %d\n", mapdata->mapheight);
	printf("mapwidth: %d\n", mapdata->mapwidth);
}


