/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:24:16 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/07 11:37:24 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putquote(char *s, int fd)
{
	size_t	i;
	char	q;

	q = '\0';
	i = 0;
	while (s[i])
	{
		if (!q && (s[i] == '\'' || s[i] == '\"'))
			q = s[i];
		else
		{
			if (q && s[i] == q)
				q = '\0';
			else
				write(fd, &s[i], 1);
		}
		i++;
	}
}
