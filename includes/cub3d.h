/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:59:06 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/22 17:09:40 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "keys.h"
# include <stdbool.h>
//# include <libft.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
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

/*  Window Settings	*/
# define WIDTH 700
# define HEIGHT 700
# define FOV 60
# define F_ 3
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64
# define MINIMAP_RATIO 4

# define NORD 0
# define SUD 1
# define WEST 3
# define EAST 2

#define SNS(a,b) a < b ? (1) : (-1)

#define M_PI       3.14159265358979323846
#define degreesToRadians(a) (a * M_PI / 180.0)
#define radiansToDegrees(a) (a * 180.0 / M_PI)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ENTITY_SZ(a) ((a == 1) ? (0.4) : (1.2)) 

typedef struct s_cub3d	t_cub3d;

// typedef struct s_mapdata
// {
// 	char	*filename;
// 	char	*north;
// 	char	*south;
// 	char	*east;
// 	char	*west;
// 	int		height;
// 	int		width;
// 	int		facing;
// 	int		floor;
// 	int		ceiling;
// 	int		map_matrix[255][255];
// 	int		start_pos[2];
// }	t_mapdata;


typedef struct s_player
{
	float	rot;
	int		fov;
	int		x;
	int		y;
	int		health;
}	t_player;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*buf;
	int			color;
	int			bpp;
	int			linelen;
	int			endian;
}	t_window;


typedef struct s_image
{
	void	*img;
	int		height;
	int		width;
	int		endiant;
	void		*mlx;
	char	*bfr;
	int		bpp;
    int		linelen;
}	t_image;

typedef struct s_entity
{
	int		type; // 0: box, 1: enemy, 2: projectile
	float		x;
	float		y;
	t_image	*sprite;
	int		en_i;
	float	dir;
	bool 	destroyed;
	bool	killed;
	bool	seen;
}	t_entity;


typedef struct s_mapdata
{
	char	*filename;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		height;
	int		saved_width;
	int		width;
	int		facing;
	int		floor;
	int		ceiling;
	int		map_matrix[255][255];
	int		start_pos[2];
}	t_mapdata;

/*GNL*/
int			ft_strlen_alt(char *dst, char *src, int siz, int alt);
char		*get_next_line(int fd);

/*PARSING CUBED #GENERAL*/
int			open_cube_file(char *filename, t_mapdata *mapdata);
int			reader(int file_fd, t_mapdata *mapdata);
int			freemapdata(t_mapdata *mapdata);
t_mapdata	*cub_parser(int argc, char **argv);

/*TEXTURES_PARSER*/
int			info_parser(char *line, t_mapdata *mapdata);
int			datamapcheck(t_mapdata *mapdata);
int			texture_files_parser(char **line_split, t_mapdata *mapdata);

/*MAP PARSER*/
int			map_validity_checker(t_mapdata *mapdata);
int			datamapcheck2(t_mapdata *mapdata, bool *mapbool, char *line);
int			cross_checker(t_mapdata *mapdata, int x, int y);
int			map_filler(int column, char *line, t_mapdata *mapdata);

/*FLOOR CEILING*/
int			fl_cl_parser(char *line, t_mapdata *mapdata);
int			fl_cl_filler(char **line_split, int *color);


struct s_cub3d
{
	t_image		*wall_textures[4];
	t_image		*sprites[2];
	t_image		*gun[4];
	t_image		*enemy[5];
	int			gun_i;
	// t_window	*minimap;
	bool		z;
	bool		q;
	bool		s;
	bool		d;
	bool		a;
	bool		e;
	t_window	*fps;
	int			last_mouse;
	t_mapdata	*map;
	t_player	*player;
	int			k_code;
	t_entity	*game_entities;
	int			entities_n;
	clock_t 	lastTime;
	clock_t 	lastFixedTime;
	int			texture_x;
	int			texture_y;
	double		Ast_frm_player;
	double		Bst_frm_player2;
	float		beta;
	double		dst_to_wall;
	float 		px;
    t_image 	*i;
	float 		py;
	float			sprite_x;
	float			sprite_y;
	bool		ht;
	int			ll;
	int			sy;
	float		pxx;
	float		pyy;
	float		sz;
	int			sx;
	int		y_y;
    float 		v_py;
    float 		v_px;
	int		real_y;
	int		real_x;
	int			fps_v;
	bool		shooting;
	double		elapsedTime;
	double		elapsedFixedTime;
	double		fps_counter;
	bool		key_pressed;
};

void    init_map(t_cub3d *t);
int		init_windows(t_cub3d *t);

// UTILS
void    init_ray_loop(t_cub3d *f);
void    throw_ray_loop(t_cub3d *f, float a);
double  terner(t_cub3d *f);
void    strafe(t_cub3d *f, float rot);
int		aa(int ll, int px, int py, t_cub3d *f);
void    reset_entities(t_cub3d *f);

// map
int		position_to_map_tiles(int px, int py, t_cub3d *f);
int		position_to_next_tile_line(t_cub3d *f, int x, int y, float a);
//void	nxt_horz_inter(float alpha, int *p_x, int *p_y, t_cub3d *f);
//void	nxt_vert_inter(float alpha, int *p_x, int *p_y, t_cub3d *f);
void	nxt_horz_stepper(float alpha, int *p_x, int *p_y, t_cub3d *f);
void	nxt_vert_stepper(float alpha, int *p_x, int *p_y, t_cub3d *f);
void	nxt_vert_inter(float alpha, float *p_x, float *p_y, t_cub3d *f);
void	nxt_horz_inter(float alpha, float *p_x, float *p_y, t_cub3d *f);

// player
void	raycasting(t_cub3d *f);
void	init_player(t_cub3d *f);
void	render_gun(t_cub3d *f);

// entities
void	check_entities(t_cub3d *f);
void    init_entities(t_cub3d *f);
void    init_projectile(t_cub3d *f, int x, int y, float dir);
void	draw_entities(t_cub3d *f);
void	render_entities(t_cub3d *f);

// minimap
void 	render(t_cub3d *f);
void 	draw_grid(t_cub3d *f);
void 	draw_walls(t_cub3d *f);

// draw
void	set_pixel_color(t_window *w, long x, long y, unsigned int n);
unsigned int	get_texture_color(t_cub3d *f, int x, int y, t_image *t);
//void	draw_line(t_window *w, int x0, int y0, int x1, int y1, int color);
void	draw_line(t_cub3d *f, int x0, int y0, int x1, int y1, int color);
// void	draw_rect(t_cub3d *f, int x0, int y0, int x1, int y1, int color);
void	draw_rect(t_cub3d *f, int x0, int y0, int x1, int y1, int color);
// void	draw_rect(t_window *f, int x0, int y0, int x1, int y1, int color);
void	draw_sprite(t_image *i, float dst_to_sprite, t_cub3d *f, float sz);
//void	draw_fps_texturedray(t_window *w, int x, float dist_to_wall, int texture_x, t_cub3d *f, t_image *texture, float a);
void	draw_fps_ray(int x, float dist_to_wall, t_cub3d *f, t_image *texture, float a);
int		fog_color(int color, float dist_to_wall);
void	shoot(t_cub3d *f);

// keyboard
int	open_hook(int k_code, t_cub3d *f);
int	close_hook(int k_code, t_cub3d *f);
int	keyboard(t_cub3d *f);
int	mouse(int x, int y, t_cub3d *f);
int	hook_mousedown(int k_code, long x, long y, t_cub3d *f);

#endif