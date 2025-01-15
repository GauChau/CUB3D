/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:11:21 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/29 15:55:46 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_len(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	_len;

	_len = str_len(to_find);
	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (j < _len && str[i + j] != '\0' && str[i + j] == to_find[j]
				&& i + j < len)
				j++;
			if (j == _len)
				return ((char *) &(str[i]));
		}
		i++;
	}
	return (0);
}
