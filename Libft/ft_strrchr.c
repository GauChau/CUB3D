/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:18:46 by julessainth       #+#    #+#             */
/*   Updated: 2025/01/22 13:59:55 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	if (s[i] == '\0' && (unsigned char)c == '\0')
		return ((char *) &(s[i]));
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *) &(s[i]));
		i--;
	}
	return (NULL);
}
