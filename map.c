/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:17:45 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/23 13:33:39 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	position_to_map_tiles(int px, int py, t_cub3d *f)
{
	if (px > WIDTH || py > HEIGHT || px < 0 || py < 0)
		return (1);
	if ((int)(px / (WIDTH / (f->map)->width)) >= (f->map)->width
		|| (int)((py / (HEIGHT / (f->map)->height))) >= (f->map)->height)
		return (1);
	if ((f->map)->map_matrix[(int)(
			(py / (HEIGHT / (f->map)->height))
		)][(int)(
			(px / (WIDTH / (f->map)->width))
		)] == '1')
	{
		return (1);
	}
	else
		return (0);
}

void	nxt_horz_inter(float alpha, float *p_x, float *p_y, t_cub3d *f)
{
	float	ay;
	float	ax;
	int		h_tick;

	h_tick = (HEIGHT / (f->map)->height);
	if (sin(degreestoradians(alpha)) > 0)
	{
		ay = (float)((*p_y) - (int)(*p_y) % h_tick) - 0.1;
	}
	else
	{
		ay = (*p_y) + (float)(h_tick - ((int)(*p_y) % h_tick));
	}
	ax = (*p_x) + (*p_y - ay) / (float)(tan(degreestoradians(alpha)));
	*p_x = ax;
	*p_y = ay;
}

void	nxt_vert_inter(float alpha, float *p_x, float *p_y, t_cub3d *f)
{
	float	ay;
	float	ax;
	int		v_tick;

	v_tick = (WIDTH / (f->map)->width);
	if (cos(degreestoradians(alpha)) < 0)
	{
		ax = (float)((*p_x) - (int)(*p_x) % v_tick) - 0.1;
	}
	else
	{
		ax = (*p_x) + (float)((v_tick - ((int)(*p_x) % v_tick)));
	}
	ay = (*p_y) + (*p_x - ax) * tan(degreestoradians(alpha));
	*p_x = ax;
	*p_y = ay;
}
