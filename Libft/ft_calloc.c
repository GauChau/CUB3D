/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:26:10 by julessainth       #+#    #+#             */
/*   Updated: 2024/06/06 11:46:51 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*c_alloc;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	c_alloc = (void *)(malloc(count * size));
	if (!c_alloc)
		return (NULL);
	ft_bzero(c_alloc, count * size);
	return (c_alloc);
}
