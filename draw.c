/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:56:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/22 17:09:32 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_cub3d *f, int x0, int y0, int x1, int y1, int color)
{
	int	err;
	int	e2;
	int	dx;
	int	dy;

	dx = abs(x1 - x0);
	f->sx = SNS(x0, x1);
	dy = -abs(y1 - y0);
	f->sy = SNS(y0, y1);
	err = dx + dy;
	while (1 && !(x0 == x1 && y0 == y1))
	{
		set_pixel_color(f->fps, x0, y0, color);
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += f->sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += f->sy;
		}
	}
}

void	draw_rect(t_cub3d *f, int x0, int y0, int x1, int y1, int color)
{
	if (x1 < x0 || y1 < y0 || x0 > WIDTH || y0 > HEIGHT)
		return ;
	while (y0 < y1)
	{
		draw_line(f, x0, y0, x1, y0, color);
		y0++;
	}
}

static void	sprite_rays(t_cub3d *f, float sprite_y, float sprite_x, int *hitler)
{
	int		aax;
	float	a;

	aax = 0;
	a = 0.001;
	while (a < FOV && (*hitler) == -1)
	{
		f->px = (float)(f->player->x);
		f->py = (float)(f->player->y);
		while (1)
		{
			if (f->px < 0.0 || (int)(f->px) > WIDTH || (int)(f->py) > HEIGHT || f->py < 0.0)
				break ;
			if ((f->px < sprite_x + 2 && f->px > sprite_x - 2)
				&& (f->py < sprite_y + 2 && f->py > sprite_y - 2))
			{
				(*hitler) = aax;
				break ;
			}
			f->px += (cos(degreesToRadians(((a - f->player->rot) - 60))));
			f->py += (sin(degreesToRadians(((a - f->player->rot) - 60))));
		}
		aax++;
		a += (float)(FOV) / (float)(WIDTH);
	}
}

void	draw_fps_ray(int x, float ds, t_cub3d *f, t_image *texture, float a)
{
	float	wall_height;
	int		texture_y;
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
	int		offset_y;
	float	x;
	float	y;
	int		hitler;

	y = 0;
	f->real_y = 0;
	hitler = -1;
	sprite_rays(f, f->sprite_y, f->sprite_x, &hitler);
	while (y < i->height)
	{
		x = 0;
		f->real_x = 0;
		while (x < i->width)
		{
			offset_y = (i->height / (dst_sprite / 100));
			if (get_texture_color(f, (int)(x), (int)(y), i) != -16777216)
			{
				set_pixel_color(f->fps,
					(hitler) + (f->real_x),
					(HEIGHT / 2) + f->real_y - (offset_y),
					get_texture_color(f, (int)(x), (int)(y), i)
					);
			}
			f->real_x++;
			x += (dst_sprite / 100) * sz;
		}
		f->real_y++;
		y += (dst_sprite / 100) * sz;
	}
}
