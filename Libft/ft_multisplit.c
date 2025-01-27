/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multisplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:14:13 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 14:17:43 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

static int	char_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static size_t	count_words(char *s, char *set)
{
	size_t	words;
	size_t	i;
	char	q;

	q = '\0';
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			q = ft_inq(q, s[i]);
		if (((char_in_set(s[i], set) >= 0 && !q) && s[i + 1] != '\0'))
			words++;
		i++;
	}
	return (words + 1);
}

static void	fill_tab(t_mltsplit *tab, char *s, char *set, size_t *i)
{
	size_t	j;
	char	q;

	q = '\0';
	j = 0;
	while (s[j] && (char_in_set(s[j], set) < 0 || q))
	{
		if (s[j] == '\'' || s[j] == '\"')
			q = ft_inq(q, s[j]);
		(tab[(*i)]).s[j] = s[j];
		j++;
	}
	(tab[(*i)]).s[j] = '\0';
	(*i)++;
	tab[(*i)].ix = char_in_set(s[j], set);
}

static void	set_mem(t_mltsplit *tab, char *s, char *set, char *q)
{
	size_t	count;
	size_t	ix;
	size_t	i;
	int		is_skip;

	is_skip = 0;
	ix = 0;
	i = 0;
	while (s[ix])
	{
		count = 0;
		while (s[ix + count] && (char_in_set(s[ix + count], set) < 0 || *q))
		{
			if (s[ix + count] == '\'' || s[ix + count] == '\"')
				*q = ft_inq(*q, s[ix + count]);
			count++;
		}
		if (count > 0 || (is_skip))
		{
			tab[i].s = malloc(sizeof(char) * (count + 1));
			fill_tab(tab, (s + ix), set, &i);
		}
		is_skip = 0;
		if (count == 0)
		{
			count = 1;
			is_skip = 1;
		}
		ix += (count);
	}
	tab[i].s = NULL;
}

t_mltsplit	*ft_multisplit(char *s, char *set)
{
	size_t		words;
	t_mltsplit	*tab;
	char		q;

	if (!s || !set || !ft_strlen(s))
		return (NULL);
	q = '\0';
	words = count_words(s, set);
	tab = malloc((words + 1) * sizeof(t_mltsplit));
	if (!tab)
		return (NULL);
	(*tab).mltsplit_l = words;
	set_mem(tab, s, set, &q);
	if (!ft_strlen(tab[0].s))
		tab[0].ix = char_in_set(*s, set);
	else
		tab[0].ix = 0;
	return (tab);
}
