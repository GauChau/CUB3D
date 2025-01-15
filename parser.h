/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautierchauvot <gautierchauvot@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:02:15 by gautierchau       #+#    #+#             */
/*   Updated: 2025/01/14 21:30:53 by gautierchau      ###   ########.fr       */
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


int		ft_strlen_alt(char *dst, char *src, int siz, int alt);
char	*get_next_line(int fd);


#endif