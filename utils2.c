/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:19:29 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/22 15:36:22 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_hook(int k_code, t_cub3d *f)
{
	if (f->k_code == -1)
	{
		return (0);
	}
	printf("k_code: %d \n", k_code);
	if (k_code == 119)
		f->z = true;
	if (k_code == 115)
		f->s = true;
	if (k_code == 97)
		f->q = true;
	if (k_code == 100)
		f->d = true;
	if (k_code == 113)
		f->a = true;
	if (k_code == 101)
		f->e = true;
	return (0);
}

int	hook_mousedown(int k_code, long x, long y, t_cub3d *f)
{
	(void)(x);
	(void)(y);
	if (k_code == 1)
		shoot(f);
}

int	aa(int ll, int px, int py, t_cub3d *f)
{
	if (ll != -1)
	{
		draw_line(f,
			f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
			px / MINIMAP_RATIO, py / MINIMAP_RATIO,
			0xFFF000
			);
	}
	else
	{
		draw_line(f,
			f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
			px / MINIMAP_RATIO, py / MINIMAP_RATIO,
			0xFF00FF
			);
	}
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
