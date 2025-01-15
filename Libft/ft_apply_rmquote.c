/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_rmquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julessainthorant <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:10:08 by julessainthor     #+#    #+#             */
/*   Updated: 2024/12/03 15:11:10 by julessainthor    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	ft_apply_rmquote(char **t)
{
	size_t	i;

	i = 0;
	while (t[i])
	{
		t[i] = ft_rm_quotes(t[i]);
		i++;
	}
	return ;
}
