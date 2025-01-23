/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:20:04 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/23 13:31:37 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	degreestoradians(float a)
{
	return ((a * M_PI / 180.0));
}

float	radiantodegrees(float a)
{
	return ((a * 180.0 / M_PI));
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

float	entity_sz(int a)
{
	if (a == 1)
		return (0.4);
	else
		return (1.2);
}

int	sns(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}
