/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:19:29 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/24 17:01:49 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	open_na_noor(t_cub3d *f)
{
	if (f->door_interact)
	{
		if ((f->map)->map_matrix[f->door_ix[0]][f->door_ix[1]]
			== 'P')
			(f->map)->map_matrix[f->door_ix[0]][f->door_ix[1]] = 'p';
		else
			(f->map)->map_matrix[f->door_ix[0]][f->door_ix[1]] = 'P';
	}
	f->f = false;
	f->door_interact = false;
}

int	open_hook(int k_code, t_cub3d *f)
{
	if (f->k_code == -1)
		return (0);
	if (k_code == 119)
		f->z = true;
	if (k_code == 32)
		shoot(f);
	if (k_code == 102)
	{
		f->f = true;
		open_na_noor(f);
	}
	if (k_code == K_ESC)
		ft_close(f);
	if (k_code == 115)
		f->s = true;
	if (k_code == 97)
		f->q = true;
	if (k_code == 100)
		f->d = true;
	if (k_code == 113 || k_code == 65361)
		f->a = true;
	if (k_code == 101 || k_code == 65363)
		f->e = true;
	return (0);
}

int	hook_mousedown(int k_code, long x, long y, t_cub3d *f)
{
	(void)(x);
	(void)(y);
	if (k_code == 1)
		shoot(f);
	return (0);
}
/*
int	aa(int ll, int px, int py, t_cub3d *f)
{
	if (ll != -1)
	{
		f->color = 0xFFF000;
		draw_line(f,
			f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
			px / MINIMAP_RATIO, py / MINIMAP_RATIO
			);
	}
	else
	{
		if (f->last_wall == '1')
			f->color = 0xFF000F;
		else
			f->color = 0xFFBBBF;
		draw_line(f,
			f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
			px / MINIMAP_RATIO, py / MINIMAP_RATIO
			);
	}
	return (0);
}
*/

int	aa(int ll, int px, int py, t_cub3d *f)
{
	if (ll != -1)
	{
		f->color = 0xFFF000;
		f->posdrw[0] = f->player->x / MINIMAP_RATIO;
		f->posdrw[1] = f->player->y / MINIMAP_RATIO;
		f->posdrw[2] = px / MINIMAP_RATIO;
		f->posdrw[3] = py / MINIMAP_RATIO;
		draw_line(f);
	}
	else
	{
		f->color = 0xFF00FF;
		f->posdrw[0] = f->player->x / MINIMAP_RATIO;
		f->posdrw[1] = f->player->y / MINIMAP_RATIO;
		f->posdrw[2] = px / MINIMAP_RATIO;
		f->posdrw[3] = py / MINIMAP_RATIO;
		draw_line(f);
	}
	return (0);
}

int	keyboard(t_cub3d *f)
{
	if (f->k_code == -1)
		return (0);
	if (f->k_code == K_ESC)
		exit(0);
	if (f->z)
		strafe(f, 0);
	if (f->s)
		strafe(f, 180);
	if (f->q)
		strafe(f, 90);
	if (f->d)
		strafe(f, -90);
	if (f->a)
		f->player->rot += 4;
	if (f->e)
		f->player->rot -= 4;
	return (0);
}

void	reset_entities(t_cub3d *f)
{
	int	i;

	i = 0;
	while (i < f->entities_n)
	{
		f->game_entities[i].seen = false;
		i++;
	}
}
