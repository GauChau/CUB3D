/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:06:05 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/22 16:19:57 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_cub3d *f)
{
	draw_rect(f,
		(f->player)->x / MINIMAP_RATIO,
		(f->player)->y / MINIMAP_RATIO,
		((f->player)->x / MINIMAP_RATIO) + 4,
		((f->player)->y / MINIMAP_RATIO) + 4,
		0x00FFFF);
}

void	draw_walls(t_cub3d *f)
{
	int	y;
	int	x;

	y = 0;
	while (y < (f->map)->height)
	{
		x = 0;
		while (x < (f->map)->width)
		{
			if ((f->map)->map_matrix[y][x] == '1')
			{
				draw_rect(f,
					(x * (WIDTH / (f->map)->width)) / MINIMAP_RATIO,
					(y * (HEIGHT / (f->map)->height)) / MINIMAP_RATIO,
					(((x + 1) * (WIDTH / (f->map)->width))) / MINIMAP_RATIO,
					(((y + 1) * (HEIGHT / (f->map)->height))) / MINIMAP_RATIO,
					0XFFFFFF
					);
			}
			x++;
		}
		y++;
	}
}

void	draw_entities(t_cub3d *f)
{
	int			i;
	int			color;
	int			sz;
	t_entity	*e;

	draw_player(f);
	i = 0;
	while (i < f->entities_n)
	{
		e = &(f->game_entities[i]);
		sz = 5;
		if (e->type == 2)
		{
			color = 0x222222;
			sz = 2;
		}
		else
			color = 0xFFFF00;
		draw_rect(f, (int)((e)->x) / MINIMAP_RATIO,
			(int)((e)->y) / MINIMAP_RATIO,
			((int)((e)->x) / MINIMAP_RATIO) + sz,
			((int)((e)->y) / MINIMAP_RATIO) + sz, color);
		i++;
	}
}
