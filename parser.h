/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:02:15 by gautierchau       #+#    #+#             */
/*   Updated: 2025/01/17 14:24:24 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <libft.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_mapdata
{
	char	*filename;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		mapheight;
	int		mapwidth;
	int		facing;
	int		floor;
	int		ceiling;
	int		map_matrix[255][255];
	int		start_pos[2];
}	t_mapdata;

/*GNL*/
int		ft_strlen_alt(char *dst, char *src, int siz, int alt);
char	*get_next_line(int fd);

/*PARSING CUBED #GENERAL*/
int		open_cube_file(char *filename, t_mapdata *mapdata);
int		reader(char *filename, int file_fd, t_mapdata *mapdata);
int		freemapdata(t_mapdata *mapdata);
int		cub_parser(int argc, char **argv);

/*TEXTURES_PARSER*/
int		info_parser(char *line, t_mapdata *mapdata);
int		datamapcheck(t_mapdata *mapdata, bool *mapbool, char *line);
int		texture_files_parser(char **line_split, t_mapdata *mapdata);

/*MAP PARSER*/
int		map_validity_checker(t_mapdata *mapdata);
int		datamapcheck2(t_mapdata *mapdata, bool *mapbool, char *line);
int		cross_checker(t_mapdata *mapdata, int x, int y);
int		map_filler(int column, char *line, t_mapdata *mapdata);

/*FLOOR CEILING*/
int		fl_cl_parser(char *line, t_mapdata *mapdata);
int		fl_cl_filler(char **line_split, int *color);

#endif