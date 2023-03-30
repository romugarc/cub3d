/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:22:30 by warnora           #+#    #+#             */
/*   Updated: 2023/02/27 19:36:06 by warnora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**ft_split_next(char **tab, const char *str, char c)
{
	int	i;
	int	l;
	int	co;

	i = 0;
	l = 1;
	co = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			tab[l][co] = str[i];
			co++;
		}
		else if (str[i] == c)
		{
			l++;
			co = 0;
		}
		i++;
	}
	return (tab);
}

static char	**space_in_tab(char **tab, const char *str, char c, int max_cl[2])
{
	int	l;
	int	co;

	l = 0;
	while (l < max_cl[1])
	{
		co = 0;
		tab[l] = malloc(sizeof(char) * max_cl[0]);
		if (!tab[l])
			fail("Malloc error\n");
		while (co < max_cl[0])
		{
			tab[l][co] = ' ';
			co++;
		}
		tab[l][co] = '\0';
		l++;
	}
	tab[l] = NULL;
	return (ft_split_next(tab, str, c));
}

static void	ft_splitv2_init(int *i, int *l, int *co, int *max_cl)
{
	(*i) = 0;
	(*l) = 0;
	(*co) = 0;
	(*max_cl) = 0;
}

char	**ft_splitv2(const char *str, char c)
{
	int		i;
	int		l;
	int		co;
	int		max_cl[2];
	char	**tab;

	ft_splitv2_init(&i, &l, &co, &max_cl[0]);
	while (str[i])
	{
		if (str[i] == c)
		{
			co = 0;
			l++;
		}
		co++;
		if (co > max_cl[0])
			max_cl[0] = co + 3;
		i++;
	}
	tab = malloc(sizeof(char *) * (l + 3));
	if (!tab)
		fail("Malloc error\n");
	max_cl[1] = l + 3;
	return (space_in_tab(tab, str, c, max_cl));
}
