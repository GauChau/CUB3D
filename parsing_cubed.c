/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cubed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautierchauvot <gautierchauvot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:59:22 by gautierchau       #+#    #+#             */
/*   Updated: 2025/01/15 10:38:49 by gautierchau      ###   ########.fr       */
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

int	texture_files_parser(char **line_split, t_mapdata *mapdata)
{
	if(line_split[2] != NULL)
		return(write(2, "too much info on texture path line\n", 35), 2);
	int axess = access(line_split[1], F_OK);
	if(axess != 0)
		return (printf("access return: %d\n", axess),perror("access file error"), 2);
	if (!ft_strcmp(line_split[0], "NO") && mapdata->north == NULL)
	{
		mapdata->north = ft_strdup(line_split[1]);
	}
	else if (!ft_strcmp(line_split[0], "SO") && !mapdata->south)
	{
		mapdata->south = ft_strdup(line_split[1]);
	}
	else if (!ft_strcmp(line_split[0], "EA") && !mapdata->east)
	{
		mapdata->east = ft_strdup(line_split[1]);
	}
	else if (!ft_strcmp(line_split[0], "WE") && !mapdata->west)
	{
		mapdata->west = ft_strdup(line_split[1]);
	}
	else if(line_split[0][0] != '\n')
		return(write(2, "error regarding texture orientation naming and or duplicates\n", 61), 2);
	return (0);
}

int	info_parser(char *line, t_mapdata *mapdata)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (texture_files_parser(line_split, mapdata))
		return (2);
	else
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

int fl_cl_parser(char *line, t_mapdata *mapdata)
{
	char	**line_split;
	int		i;
	char	**trimed;

	i = 0;
	line_split = ft_split(line, ' ');
	printf("line split[0]: @%s@\n", line_split[0]);
	printf("line split[1]: @%s@\n", line_split[1]);
	if (line_split[2])
		return(write(2, "too much info on floor/ceiling color line\n", 42), 2);
	if (!ft_strcmp(line_split[0], "F") && mapdata->floor == -1)
	{
		trimed = ft_split(line_split[1], ',');
		if (trimed[3] || !trimed[0] || !trimed[1] || !trimed[2])
			return(write(2, "wrong floor color\n", 18), 2);
		mapdata->floor = rgb_to_int(trimed[0], trimed[1], trimed[2]);
		if (mapdata->floor == -2)
			return(write(2, "wrong floor color\n", 18), 2);
		ft_free_tab(trimed);
		ft_free_tab(line_split);
		return (0);
	}
	else if (!ft_strcmp(line_split[0], "C") && mapdata->ceiling == -1)
	{
		trimed = ft_split(line_split[1], ',');
		if (trimed[3] || !trimed[0] || !trimed[1] || !trimed[2])
			return(write(2, "wrong ceiling color\n", 20), 2);
		mapdata->ceiling = rgb_to_int(trimed[0], trimed[1], trimed[2]);
		if (mapdata->ceiling == -2)
			return(write(2, "wrong ceiling color\n", 20), 2);
		ft_free_tab(trimed);
		ft_free_tab(line_split);
		return (0);
	}
	else 
		return(printf("clparser last 2, line: @%s@\n", line),2);
	return (1);
}

int	starter_checker(int c, t_mapdata *mapdata)
{
	if (ft_char_in_set(c, "NSEW") && mapdata->north)
		return (printf("starter pos duplicate"), 2);
	else
		;
}
int map_filler(int column, char *line, t_mapdata *mapdata)
{
	int	i;

	i = 0;
	if (ft_strlen(line) > 255)
		return (2);
	while (line[i])
	{
		if (!ft_char_in_set(line[i], " 01NSEW\n"))
			return (2);
		if (ft_char_in_set(line[i], "NSEW") && mapdata->start_pos[0] != -1)
			return (printf("starter pos duplicate"), 2);
		else
		{
			mapdata->start_pos[0] = i;
			mapdata->start_pos[1] = column;
		}
		mapdata->map_matrix[column][i] = line[i];
		i++;
	}
	
}

int	reader(char *filename, int file_fd, t_mapdata *mapdata)
{
	char	*line;
	int		column;

	column = 0;
	while (1)
	{
		line = get_next_line(file_fd);
		if (!line || line[0] == 0)
			break ;
		printf("gnl: %s\n", line);
		if (ft_strlen(line) == 0 || (ft_strlen(line) == 1 && line[0] == '\n'))
			continue ;
		if (ft_strchr(line, '\n'))
			ft_strchr(line, '\n')[0] = 0;
		if(!mapdata->north || !mapdata->south || !mapdata->west || !mapdata->east)
		{
			if (info_parser(line, mapdata))
				break ;
		}
		else if(mapdata->ceiling == -1 || mapdata->floor == -1)
		{
			if (fl_cl_parser(line, mapdata))
			{
				printf("flcl parser fail on: @%s@\n", line);
				break ;
			}
		}
		else
		{
			if (map_filler(column, line, mapdata) == 2)
				return (printf("wrong map data\n"), 2);
			column++;
		}
	}
}

int open_cube_file(char *filename, t_mapdata *mapdata)
{
	int	file_fd;

	mapdata->start_pos[0] = -1;
	mapdata->ceiling = -1;
	mapdata->floor = -1;
	file_fd = open(filename, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		perror("cub3d: ");
		return (-1);
	}
	else
	{
		reader(filename, file_fd, mapdata);
	}
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
	open_cube_file(argv[1], mapdata);
	// printf("mapnorth: %s\n", mapdata->north);
	// printf("mapnsouth: %s\n", mapdata->south);
	// printf("mapneast: %s\n", mapdata->east);
	// printf("mapnwest: %s\n", mapdata->west);
	printf("floor: %d\n", mapdata->floor);
	printf("ceiling: %d\n", mapdata->ceiling);
}


