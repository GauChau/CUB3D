/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:20:10 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/24 18:08:07 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_imgs(t_cub3d *f)
{
	int	i;

	i = 0;
	load_sprite_files(f);
	while (i < 5)
	{
		printf("i: %d, f->wls[i]:%s \n", i, f->wls[i]);
		f->wall_textures[i] = ft_calloc(1, sizeof(t_image));
		if (!f->wall_textures[i])
			return (-1);
		f->wall_textures[i]->img = mlx_xpm_file_to_image(f->fps->mlx,
				(f->wls[i]),
				&f->wall_textures[i]->width, &f->wall_textures[i]->height);
		if (!f->wall_textures[i]->img)
			return (-1);
		f->wall_textures[i]->bfr = mlx_get_data_addr(f->wall_textures[i]->img,
				&f->wall_textures[i]->bpp,
				&f->wall_textures[i]->linelen, &f->wall_textures[i]->endiant);
		i++;
	}
	if (load_gun(f) != 1)
		return (-1);
	if (load_sprite(f) != 1 || load_enemy(f) != 1)
		return (-1);
	return (1);
}

int	init_things(t_cub3d *f, int argc, char **argv)
{
	f->map = cub_parser(argc, argv);
	if (!f->map)
		return (free(f), -1);
	f->lasttime = clock();
	f->player = malloc(sizeof(t_player));
	f->last_mouse = -1;
	if (!f || !(f->player) || !f->map)
		return (-1);
	if (! init_windows(f))
		return (-1);
	(f->player)->rot = 0;
	if (load_imgs(f) != 1)
	{
		printf("LOADING TEXTURES ERRROR AT %d \n", load_imgs(f));
		return (-1);
	}
	return (0);
}

void	shoot(t_cub3d *f)
{
	float	p;

	if (f->shooting)
		return ;
	f->shooting = true;
	f->gun_i = 0;
	p = (f->player)->rot;
	init_projectile(f, f->player->x, f->player->y, p + 30);
}

float	s_func(t_cub3d *f)
{
	if (f->s_type == 2)
		return (3);
	else
		return (1);
}

float	f_rot(char c)
{
	if (c == 'W')
		return (180 - (FOV / 2));
	if (c == 'E')
		return (0 - (FOV / 2));
	if (c == 'N')
		return (90 - (FOV / 2));
	if (c == 'S')
		return (270 - (FOV / 2));
}
