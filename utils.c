/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:38:05 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/23 13:34:59 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_loop(t_cub3d *f)
{
	f->px = (float)(f->player->x);
	f->py = (float)(f->player->y);
	f->v_px = (float)(f->player->x);
	f->v_py = (float)(f->player->y);
	f->beta = f->beta - (float)(FOV) / (float)(WIDTH);
	f->i = f->wall_textures[0];
}

void	throw_ray_loop(t_cub3d *f, float a)
{
	int	k;

	k = 0;
	while (k < 200)
	{
		if (!(position_to_map_tiles(f->px, f->py, f) > 0
				|| f->px > WIDTH || f->py > HEIGHT))
			nxt_horz_inter(a + f->player->rot, &f->px, &f->py, f);
		if (!(position_to_map_tiles(f->v_px, f->v_py, f) > 0
				|| f->v_px > WIDTH || f->v_py > HEIGHT))
			nxt_vert_inter(a + f->player->rot, &f->v_px, &f->v_py, f);
		f->Ast_frm_player = (sqrt(pow((float)(f->px) - (float)(f->player->x), 2)
					+ pow((float)(f->py) - (float)(f->player->y), 2)));
		f->Bst_frm_player2 = (sqrt(pow(f->v_px - (float)f->player->x, 2)
					+ pow((float)(f->v_py) - (float)(f->player->y), 2)));
		k++;
	}
	if (f->Ast_frm_player > f->Bst_frm_player2)
	{
		f->dst_to_wall = f->Bst_frm_player2;
		f->px = f->v_px;
		f->py = f->v_py;
	}
	else
		f->dst_to_wall = f->Ast_frm_player;
}

double	terner(t_cub3d *f)
{
	if (f->Ast_frm_player > f->Bst_frm_player2)
		return (f->texture_y);
	else
		return (f->texture_x);
}

void	strafe(t_cub3d *f, float rot)
{
	if (position_to_map_tiles(
			(f->player)->x + 13
			*(cos(degreestoradians((f->player->rot + FOV / 2 + (rot))))),
			(f->player)->y - 13
			*(sin(degreestoradians((f->player->rot + FOV / 2 + (rot))))),
			f) != 1)
	{
		(f->player)->x += roundf(6 * (
					cos(degreestoradians((f->player->rot + FOV / 2 + rot)))));
		(f->player)->y -= roundf(6 * (
					sin(degreestoradians((f->player->rot + FOV / 2 + rot)))));
	}
}

int	mouse(int x, int y, t_cub3d *f)
{
	(void)(x);
	(void)(y);
	if (f->last_mouse < x)
	{
		(f->player)->rot -= 1;
	}
	else if (f->last_mouse > x)
	{
		(f->player)->rot += 1;
	}
	return (0);
}
