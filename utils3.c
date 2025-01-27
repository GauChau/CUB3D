/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:31:33 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/24 12:45:31 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
// walls
const char *a[4] = {
	"./textures/01.xpm",
	"./textures/02.xpm",
	"./textures/01.xpm",
	"./textures/texture_03.xpm"
};

// sprite
const char *b[2] = {
	"./textures/enemy.xpm",
	"./textures/BULLET.xpm"
};
// gun
const char *c[4] = {
	"./textures/t0.xpm",
	"./textures/t1.xpm",
	"./textures/t2.xpm",
	"./textures/t3.xpm",
};
// enemy
const char *d[5] = {
	"./textures/ea.xpm",
	"./textures/eb.xpm",
	"./textures/ec.xpm",
	"./textures/ed.xpm",
	"./textures/ee.xpm"
};
*/

void	bullet_collisions(t_cub3d *f, int l)
{
	int	m;

	m = 0;
	while (m < f->entities_n)
	{
		if (f->game_entities[m].type == 1 && !f->game_entities[m].killed)
		{
			if (((f->game_entities[l].x < f->game_entities[m].x + 15)
					&& (f->game_entities[l].x > f->game_entities[m].x - 15))
				&& ((f->game_entities[l].y < f->game_entities[m].y + 15)
					&& (f->game_entities[l].y > f->game_entities[m].y - 15))
			)
			{
				f->game_entities[l].destroyed = true;
				f->game_entities[m].killed = true;
				break ;
			}
		}
		m++;
	}
}

void	load_sprite_files(t_cub3d *f)
{
	f->wls[0] = "./textures/01.xpm";
	f->wls[1] = "./textures/02.xpm";
	f->wls[2] = "./textures/01.xpm";
	f->wls[3] = "./textures/texture_03.xpm";
	f->wls[4] = "./textures/door.xpm";
	f->sp[0] = "./textures/enemy.xpm";
	f->sp[1] = "./textures/BULLET.xpm";
	f->gn[0] = "./textures/t0.xpm";
	f->gn[1] = "./textures/t1.xpm";
	f->gn[2] = "./textures/t2.xpm";
	f->gn[3] = "./textures/t3.xpm";
	f->enm[0] = "./textures/ea.xpm";
	f->enm[1] = "./textures/eb.xpm";
	f->enm[2] = "./textures/ec.xpm";
	f->enm[3] = "./textures/ed.xpm";
	f->enm[4] = "./textures/ee.xpm";
}

int	load_sprite(t_cub3d *f)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		f->sprites[i] = calloc(1, sizeof(t_image));
		if (!f->sprites[i])
			return (-2);
		f->sprites[i]->img = mlx_xpm_file_to_image(f->fps->mlx, f->sp[i],
				&f->sprites[i]->width, &f->sprites[i]->height);
		if (!f->sprites[i]->img)
			return (-2);
		f->sprites[i]->bfr = mlx_get_data_addr(f->sprites[i]->img,
				&f->sprites[i]->bpp,
				&f->sprites[i]->linelen, &f->sprites[i]->endiant);
		i++;
	}
	return (1);
}

int	load_gun(t_cub3d *f)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		f->gun[i] = malloc(sizeof(t_image));
		if (!f->gun[i])
			return (-3);
		f->gun[i]->img = mlx_xpm_file_to_image(f->fps->mlx, (char *)(f->gn[i]),
				&f->gun[i]->width, &f->gun[i]->height);
		if (!f->gun[i]->img)
			return (-3);
		f->gun[i]->bfr = mlx_get_data_addr(f->gun[i]->img, &f->gun[i]->bpp,
				&f->gun[i]->linelen, &f->gun[i]->endiant);
		i++;
	}
	return (1);
}

int	load_enemy(t_cub3d *f)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		f->enemy[i] = malloc(sizeof(t_image));
		if (!f->enemy[i])
			return (-3);
		f->enemy[i]->img = mlx_xpm_file_to_image(f->fps->mlx,
				(char *)(f->enm[i]),
				&f->enemy[i]->width, &f->enemy[i]->height);
		if (!f->enemy[i]->img)
			return (-3);
		f->enemy[i]->bfr = mlx_get_data_addr(f->enemy[i]->img,
				&f->enemy[i]->bpp,
				&f->enemy[i]->linelen, &f->enemy[i]->endiant);
		i++;
	}
	return (1);
}
