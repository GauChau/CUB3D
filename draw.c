/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:56:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/23 14:27:10 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
drw_ps[4]:
	0:x0
	1:y0
	2:x1
	3:y1
*/
/*
dx = abs(x1 - x0);
f->sx = sns(x0, x1);
dy = -abs(y1 - y0);
f->sy = sns(y0, y1);
err = dx + dy;
	while (1 && !(x0 == x1 && y0 == y1))
	{
		set_pixel_color(f->fps, x0, y0, f->color);
	}
*/

void	draw_line(t_cub3d *f)
{
	int	err;
	int	e2;
	int	dx;
	int	dy;

	dx = abs(f->posdrw[2] - f->posdrw[0]);
	f->sx = sns(f->posdrw[0], f->posdrw[2]);
	dy = -abs(f->posdrw[3] - f->posdrw[1]);
	f->sy = sns(f->posdrw[1], f->posdrw[3]);
	err = dx + dy;
	while (1 && !(f->posdrw[0] == f->posdrw[2] && f->posdrw[1] == f->posdrw[3]))
	{
		set_pixel_color(f->fps, f->posdrw[0], f->posdrw[1], f->color);
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			f->posdrw[0] += f->sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			f->posdrw[1] += f->sy;
		}
	}
}
/*if (x1 < x0 || y1 < y0 || x0 > WIDTH || y0 > HEIGHT)
	return ;
while (y0 < y1)
{
	draw_line(f);
	y0++;
}
*/

void	draw_rect(t_cub3d *f)
{
	if (f->posdrw[2] < f->posdrw[0] || f->posdrw[3] < f->posdrw[1]
		|| f->posdrw[0] > WIDTH || f->posdrw[1] > HEIGHT)
		return ;
	while (f->posdrw[1] < f->posdrw[3])
	{
		draw_line(f);
		f->posdrw[1]++;
	}
}

static void	sprite_rays(t_cub3d *f, float sprite_y, float sprite_x, int *hitler)
{
	float	a;

	f->aax = 0;
	a = 0.001;
	while (a < FOV && (*hitler) == -1)
	{
		f->px = (float)(f->player->x);
		f->py = (float)(f->player->y);
		while (1)
		{
			if (f->px < 0.0 || (int)(f->px) > WIDTH
				|| (int)(f->py) > HEIGHT || f->py < 0.0)
				break ;
			if ((f->px < sprite_x + 2 && f->px > sprite_x - 2)
				&& (f->py < sprite_y + 2 && f->py > sprite_y - 2))
			{
				(*hitler) = f->aax;
				break ;
			}
			f->px += (cos(degreestoradians(((a - f->player->rot) - 60))));
			f->py += (sin(degreestoradians(((a - f->player->rot) - 60))));
		}
		f->aax++;
		a += (float)(FOV) / (float)(WIDTH);
	}
}

void	draw_fps_ray(int x, float ds, t_cub3d *f, t_image *texture)
{
	float	wall_height;
	int		y;

	wall_height = (float)(HEIGHT) / (float)ds;
	wall_height *= (float)(HEIGHT * (f->map->height * 0.0015));
	y = 0;
	while (y < HEIGHT)
	{
		if (y <= (HEIGHT / 2) - (wall_height / (2)))
			set_pixel_color(f->fps, x, y, 0xDDDDDD);
		else if (y >= (HEIGHT / 2) + (wall_height / (2)))
			set_pixel_color(f->fps, x, y,
				get_texture_color(f, 0, 0, f->wall_textures[0]));
		else
		{
			f->y_y = y - ((HEIGHT / 2) - (wall_height / 2));
			set_pixel_color(f->fps, x, y,
				fog_color(get_texture_color(f,
						terner(f),
						((float)(f->y_y) / wall_height)
						* TEXTURE_HEIGHT, texture), ds));
		}
		y++;
	}
}

void	draw_sprite(t_image *i, float dst_sprite, t_cub3d *f, float sz)
{
	f->yy_ = 0;
	f->real_y = 0;
	f->hitler = -1;
	sprite_rays(f, f->sprite_y, f->sprite_x, &f->hitler);
	while (f->yy_ < i->height)
	{
		f->xx_ = 0;
		f->real_x = 0;
		while (f->xx_ < i->width)
		{
			if (get_texture_color(f, (int)(f->xx_),
				(int)(f->yy_), i) != -16777216)
			{
				set_pixel_color(f->fps,
					(f->hitler) + (f->real_x),
					(HEIGHT / 2) + f->real_y - (i->height / (dst_sprite / 100)),
					get_texture_color(f, (int)(f->xx_), (int)(f->yy_), i)
					);
			}
			f->real_x++;
			f->xx_ += (dst_sprite / 100) * sz;
		}
		f->real_y++;
		f->yy_ += (dst_sprite / 100) * sz;
	}
}
