/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:17:35 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/29 15:56:43 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*heap_s;

	i = 0;
	while (s[i] != '\0')
		i++;
	heap_s = (char *)malloc((i + 1) * sizeof(char));
	if (!heap_s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		heap_s[i] = s[i];
		i++;
	}
	heap_s[i] = '\0';
	return (heap_s);
}
