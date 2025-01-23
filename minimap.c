/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:06:05 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/23 14:18:08 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_posdrwalls(t_cub3d *f, int x, int y)
{
	f->posdrw[0] = (x * (WIDTH / (f->map)->width)) / MINIMAP_RATIO;
	f->posdrw[1] = (y * (HEIGHT / (f->map)->height)) / MINIMAP_RATIO;
	f->posdrw[2] = (((x + 1) * (WIDTH / (f->map)->width))) / MINIMAP_RATIO;
	f->posdrw[3] = (((y + 1) * (HEIGHT / (f->map)->height))) / MINIMAP_RATIO;
}

void	set_posdrentities(t_cub3d *f, t_entity *e, int sz)
{
	f->posdrw[0] = (int)((e)->x) / MINIMAP_RATIO;
	f->posdrw[1] = (int)((e)->y) / MINIMAP_RATIO;
	f->posdrw[2] = ((int)((e)->x) / MINIMAP_RATIO) + sz;
	f->posdrw[3] = ((int)((e)->y) / MINIMAP_RATIO) + sz;
}

static void	draw_player(t_cub3d *f)
{
	f->color = 0x00FFFF;
	f->posdrw[0] = (f->player)->x / MINIMAP_RATIO;
	f->posdrw[1] = (f->player)->y / MINIMAP_RATIO;
	f->posdrw[2] = ((f->player)->x / MINIMAP_RATIO) + 4;
	f->posdrw[3] = ((f->player)->y / MINIMAP_RATIO) + 4;
	draw_rect(f);
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
				f->color = 0XFFFFFF;
				set_posdrwalls(f, x, y);
				draw_rect(f);
			}
			x++;
		}
		y++;
	}
}

/*posdrw[4]:
0:x0
1:y0
2:x1
3:y1*/
void	draw_entities(t_cub3d *f)
{
	int			i;
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
			f->color = 0x222222;
			sz = 2;
		}
		else
			f->color = 0xFFFF00;
		set_posdrentities(f, e, sz);
		draw_rect(f);
		i++;
	}
}
