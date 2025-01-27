/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:58:53 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/24 18:07:06 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fixedupdate(t_cub3d *f, clock_t current_time)
{
	int	l;

	l = 0;
	while (l < f->entities_n)
	{
		if (f->game_entities[l].destroyed || f->game_entities[l].x == 0)
		{
			l++;
			continue ;
		}
		if (f->game_entities[l].type == 2)
		{
			f->game_entities[l].x += (12)
				* (cos(degreestoradians((f->game_entities[l].dir))));
			f->game_entities[l].y -= (12)
				* (sin(degreestoradians((f->game_entities[l].dir))));
			if (position_to_map_tiles(f->game_entities[l].x,
					f->game_entities[l].y, f) == 1)
				f->game_entities[l].destroyed = true;
			else
				bullet_collisions(f, l);
		}
		l++;
	}
	f->lastfixedtime = current_time;
}

static void	update(t_cub3d *f, clock_t current_time)
{
	int	m;

	m = 0;
	f->fps_v = (int)((double)f->fps_counter / f->elapsedtime);
	f->fps_counter = 0;
	f->lasttime = current_time;
	while (m < f->entities_n)
	{
		if (f->game_entities[m].type == 1)
			f->game_entities[m].sprite = f->enemy[f->game_entities[m].en_i];
		if (f->game_entities[m].type == 1 && f->game_entities[m].killed)
			if (f->game_entities[m].en_i < 4)
				f->game_entities[m].en_i++;
		m++;
	}
	if (f->shooting)
	{
		if (f->gun_i < 3)
			f->gun_i++;
		else
		{
			f->gun_i = 0;
			f->shooting = false;
		}
	}
}

int	render_next_frame(t_cub3d *f)
{
	clock_t	current_time;
	char	a[40];

	current_time = clock();
	keyboard(f);
	render(f);
	f->fps_counter++;
	f->elapsedtime = (double)(current_time - f->lasttime) / CLOCKS_PER_SEC;
	f->elapsedfixedtime = (double)(current_time - f->lastfixedtime)
		/ CLOCKS_PER_SEC;
	if (f->elapsedfixedtime >= 0.008)
		fixedupdate(f, current_time);
	if (f->elapsedtime >= 0.12)
		update(f, current_time);
	sprintf(a, "%d", (int)(f->fps_v));
	mlx_string_put(f->fps->mlx, f->fps->win, WIDTH / 2, 30, 0xFFFFFF, "CUB3D");
	mlx_string_put(f->fps->mlx, f->fps->win, WIDTH / 2, 45, 0xFFFFFF, a);
	mlx_string_put(f->fps->mlx, f->fps->win, WIDTH / 2 + 20,
		45, 0xFFFFFF, "FPS");
	if (f->door_interact)
		mlx_string_put(f->fps->mlx, f->fps->win, WIDTH / 2,
			HEIGHT / 2, 0xFFFFFF, "PRESS (F) to open na noor");
	return (0);
}

int	ft_close(void *p)
{
	t_cub3d	*f;

	f = (t_cub3d *)(p);
	clean_exit(f);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	*f;

	f = ft_calloc(1, sizeof(t_cub3d));
	(void)(argc);
	(void)(argv);
	if (init_things(f, argc, argv) == -1)
		return (EXIT_FAILURE);
	if ((f->map)->height > (f->map)->width)
		f->map->width = f->map->height;
	else
		f->map->height = f->map->width;
	init_player(f);
	init_entities(f);
	mlx_mouse_hide(f->fps->mlx, f->fps->win);
	mlx_hook(f->fps->win, 6, 1L << 6, mouse, f);
	mlx_hook(f->fps->win, 2, 1L << 0, open_hook, f);
	mlx_hook(f->fps->win, 3, 1L << 1, close_hook, f);
	mlx_hook(f->fps->win, 4, 1L << 2, hook_mousedown, f);
	mlx_hook(f->fps->win, 17, 0, ft_close, f);
	mlx_loop_hook(f->fps->mlx, render_next_frame, f);
	mlx_loop(f->fps->mlx);
	return (0);
}
