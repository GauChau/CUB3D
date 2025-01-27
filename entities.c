/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:41:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/24 18:06:45 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_entities(t_cub3d *f)
{
	int	x;
	int	y;

	y = 0;
	f->game_entities = calloc(100, sizeof(t_entity));
	while (y < (f->map)->height)
	{
		x = 0;
		while (x < (f->map)->width)
		{
			if ((f->map)->map_matrix[y][x] == '$')
			{
				f->game_entities[f->entities_n].x
					= (x * (WIDTH / (f->map)->width));
				f->game_entities[f->entities_n].y
					= (y * (HEIGHT / (f->map)->height));
				f->game_entities[f->entities_n].destroyed = false;
				f->game_entities[f->entities_n].seen = false;
				f->game_entities[f->entities_n].type = 1;
				f->entities_n++;
			}
			x++;
		}
		y++;
	}
}

void	init_projectile(t_cub3d *f, int x, int y, float dir)
{
	int	n;

	n = f->entities_n;
	f->game_entities[n].dir = dir;
	f->game_entities[n].destroyed = false;
	f->game_entities[n].seen = false;
	f->game_entities[n].type = 2;
	f->game_entities[n].x = x;
	f->game_entities[n].y = y;
	f->game_entities[n].sprite = f->sprites[1];
	f->entities_n++;
}

static void	wawer(t_cub3d *f, int px, int py)
{
	int	l;

	l = 0;
	while (l < f->entities_n)
	{
		if (f->game_entities[l].destroyed)
		{
			l++;
			continue ;
		}
		if ((px < f->game_entities[l].x + 5
				&& px > f->game_entities[l].x - 5)
			&& (py < f->game_entities[l].y + 5
				&& py > f->game_entities[l].y - 5))
		{
			f->game_entities[l].seen = true;
			f->ht = true;
			f->ll = l;
			break ;
		}
		l++;
	}
}

void	check_entities(t_cub3d *f)
{
	float	px;
	float	py;
	float	a;

	a = 0.001;
	reset_entities(f);
	while (a < FOV)
	{
		f->ht = false;
		px = (float)(f->player->x);
		py = (float)(f->player->y);
		f->ll = -1;
		while (1)
		{
			if ((int)(px) > WIDTH || (int)(py) > HEIGHT
				|| position_to_map_tiles((px), (py), f) == 1)
				break ;
			px += (cos(degreestoradians(((a - f->player->rot) - 60))));
			py += (sin(degreestoradians(((a - f->player->rot) - 60))));
			wawer(f, px, py);
			aa(f->ll, px, py, f);
		}
		a += ((float)(FOV) / (float)(WIDTH)) * 50;
	}
}

void	render_entities(t_cub3d *f)
{
	int		l;
	float	dst;

	l = 0;
	while (l < f->entities_n)
	{
		if (f->game_entities[l].seen)
		{
						f->s_type = f->game_entities[l].type;
			dst = (sqrt(pow((float)(f->game_entities[l].x)
							- (float)(f->player->x), 2)
						+ pow((float)(f->game_entities[l].y)
							- (float)(f->player->y), 2)));
			if (dst > 20.0)
			{
				f->sprite_y = f->game_entities[l].y;
				f->sprite_x = f->game_entities[l].x;
				draw_sprite(f->game_entities[l].sprite, dst,
					f, entity_sz(f->game_entities[l].type)
					);
			}
		}
		l++;
	}
}
