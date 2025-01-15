/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:20:36 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/07 11:49:41 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isalpha(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]))
			return (0);
		i++;
	}
	return (1);
}
