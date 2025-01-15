/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:13:28 by gchauvot          #+#    #+#             */
/*   Updated: 2024/10/15 13:13:26 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
//#include "get_next_line_bonus.h"
#include "libft.h"

int	gnl_strlen(char *dst, char *src, int siz, int alt)
{
	int	i;

	i = 0;
	if (alt == 1)
	{
		if (!dst)
			return (0);
		while (dst[i] != '\0')
			i++;
		return (i);
	}
	if (alt == 2)
	{
		while (src[i] != '\0' && i + 1 < siz)
		{
			dst[i] = src[i];
			i++;
		}
		if (siz > 0)
			dst[i] = '\0';
	}
	return (i);
}
