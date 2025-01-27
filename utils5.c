/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:16:43 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/27 11:16:31 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clean_exit(t_cub3d *f)
{
	if (f->fps->img)
		mlx_destroy_image(f->fps->mlx, f->fps->img);
	if (f->fps->win)
		mlx_destroy_window(f->fps->mlx, f->fps->win);
	if (f->fps->mlx)
	{
		mlx_destroy_display(f->fps->mlx);
		free(f->fps->mlx);
	}
	free(f->map->filename);
	free(f->map->east);
	free(f->map->west);
	free(f->map->north);
	free(f->map->south);
	free(f->map);
	exit(0);
}

void	giga_lenine(t_cub3d *f, float a)
{
	float	px;
	float	py;

	px = (f->player)->x;
	py = (f->player)->y;
	if ((f->map)->map_matrix[(int)(
			(py / (HEIGHT / (f->map)->height))
		)][(int)(
		(px / (WIDTH / (f->map)->width))
	)] == 'p')
		return ;
	px += ((WIDTH / (f->map)->width) * 0.85)
		* (cos(degreestoradians(((a - f->player->rot) - 60))));
	py += ((HEIGHT / (f->map)->height) * 0.85)
		* (sin(degreestoradians(((a - f->player->rot) - 60))));
	if ((f->map)->map_matrix[(int)(
			(py / (HEIGHT / (f->map)->height))
		)][(int)(
		(px / (WIDTH / (f->map)->width))
	)] == 'p')
	{
		f->door_interact = true;
		f->door_ix[0] = (int)((py / (HEIGHT / (f->map)->height)));
		f->door_ix[1] = (int)((px / (WIDTH / (f->map)->width)));
	}
}

void	staline(t_cub3d *f)
{
	if ((f->map)->map_matrix[(int)(
			(f->py / (HEIGHT / (f->map)->height))
		)][(int)(
		(f->px / (WIDTH / (f->map)->width))
	)] == 'P' || (f->map)->map_matrix[(int)(
		(f->py / (HEIGHT / (f->map)->height))
	)][(int)(
		(f->px / (WIDTH / (f->map)->width))
	)] == 'p')
	{
		f->door_interact = true;
		f->door_ix[0] = (int)(
				(f->py / (HEIGHT / (f->map)->height))
				);
		f->door_ix[1] = (int)(
				(f->px / (WIDTH / (f->map)->width))
				);
	}
	else
		f->door_interact = false;
}
