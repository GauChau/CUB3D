/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m_strchr_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:39:32 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/02 15:02:38 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_m_strchr_i(const char *string, char a, char b)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)string;
	while ((*str != a && *str != b) && *str != 0)
	{
		str++;
		i++;
	}
	if (*str == a || *str == b)
		return (i);
	else
		return (-1);
}
