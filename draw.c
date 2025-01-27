/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:56:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/24 18:09:30 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	draw_line(t_cub3d *f, int x0, int y0, int x1, int y1)
{
	int	err;
	int	e2;
	int	dx;
	int	dy;

	dx = abs(x1 - x0);
	f->sx = sns(x0, x1);
	dy = -abs(y1 - y0);
	f->sy = sns(y0, y1);
	err = dx + dy;
	while (1 && !(x0 == x1 && y0 == y1))
	{
		set_pixel_color(f->fps, x0, y0, f->color);
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


void	draw_rect(t_cub3d *f, int x0, int y0, int x1, int y1)
{
	if (x1 < x0 || y1 < y0 || x0 > WIDTH || y0 > HEIGHT)
		return ;
	while (y0 < y1)
	{
		draw_line(f, x0, y0, x1, y0);
		y0++;
	}
}
*/
void	draw_line(t_cub3d *f)
{
	int	err;
	int	e2;
	int	dxy[2];
	int	bank[2];

	bank[0] = f->posdrw[0];
	bank[1] = f->posdrw[1];
	dxy[0] = abs(f->posdrw[2] - f->posdrw[0]);
	f->sx = sns(f->posdrw[0], f->posdrw[2]);
	dxy[1] = -abs(f->posdrw[3] - f->posdrw[1]);
	f->sy = sns(f->posdrw[1], f->posdrw[3]);
	err = dxy[0] + dxy[1];
	while (1 && !(bank[0] == f->posdrw[2] && bank[1] == f->posdrw[3]))
	{
		set_pixel_color(f->fps, bank[0], bank[1], f->color);
		e2 = 2 * err;
		if (e2 >= dxy[1])
			err += dxy[1];
		if (e2 >= dxy[1])
			bank[0] += f->sx;
		if (e2 <= dxy[0])
			err += dxy[0];
		if (e2 <= dxy[0])
			bank[1] += f->sy;
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
	int	bank;

	bank = f->posdrw[3];
	if (f->posdrw[2] < f->posdrw[0] || f->posdrw[3] < f->posdrw[1]
		|| f->posdrw[0] > WIDTH || f->posdrw[1] > HEIGHT)
		return ;
	while (f->posdrw[1] < bank)
	{
		f->posdrw[3] = f->posdrw[1];
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

	wall_height = 17000 / (float)ds;
	y = 0;
	while (y < HEIGHT)
	{
		if (y <= (HEIGHT / 2) - (wall_height / (2)))
			set_pixel_color(f->fps, x, y, f->map->ceiling);
		else if (y >= (HEIGHT / 2) + (wall_height / (2)))
			set_pixel_color(f->fps, x, y, f->map->floor);
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

void	draw_sprite(t_image *i, float d, t_cub3d *f, float sz)
{
	f->yy_ = 0;
	f->real_y = 0;
	f->hitrel = -1;
	sprite_rays(f, f->sprite_y, f->sprite_x, &f->hitrel);
	while (f->yy_ < i->height)
	{
		f->xx_ = 0;
		f->real_x = 0;
		while (f->xx_ < i->width)
		{
			if (get_texture_color(f, (int)(f->xx_),
				(int)(f->yy_), i) != -16777216)
			{
				set_pixel_color(f->fps, (f->hitrel) + (f->real_x)
					- ((i->width / (d / 100)) / s_func(f)),
					(HEIGHT / 2) + f->real_y
					- ((i->height / (d / 100)) / s_func(f)),
					get_texture_color(f, (int)(f->xx_), (int)(f->yy_), i));
			}
			f->real_x++;
			f->xx_ += (d / 100) * sz;
		}
		f->real_y++;
		f->yy_ += (d / 100) * sz;
	}
}
