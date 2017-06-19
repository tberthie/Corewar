/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:45:25 by gthomas           #+#    #+#             */
/*   Updated: 2017/06/15 11:41:28 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static int	cnt_line(char *s)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			++cnt;
		++i;
	}
	if (s[i - 1] != '\n')
		++cnt;
	return (cnt);
}

static char	**alloc_str(char *s, char **new, int i)
{
	int nb;
	int j;

	nb = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != '\n' && s[i] != '\0')
		{
			++nb;
			++i;
		}
		if (s[i] == '\n' || s[i] == '\0')
		{
			if (!(new[j] = (char *)malloc(nb + 1)))
				return (NULL);
			++i;
			++j;
			nb = 0;
		}
	}
	return (new);
}

static int	fill_str(char *s, int i, char **new, int nb)
{
	int k;
	int j;

	k = 0;
	j = 0;
	while (s[i] && j < nb)
	{
		while (s[i] != '\n' && s[i] != '\0')
		{
			new[j][k] = s[i];
			++i;
			++k;
		}
		if (s[i] == '\n' || s[i] == '\0')
		{
			new[j][k] = '\0';
			++j;
			k = 0;
		}
		++i;
	}
	return (j);
}

char		**ft_splitline(char *s)
{
	char	**new;
	int		i;
	int		j;
	int		nb;

	i = 0;
	j = 0;
	nb = 0;
	if (s && ft_strlen(s) > 0)
	{
		if (!(nb = cnt_line(s)))
			return (NULL);
		if (!(new = (char **)malloc((nb + 1) * sizeof(char *))))
			return (NULL);
		new = alloc_str(s, new, 0);
		new[fill_str(s, 0, new, nb)] = NULL;
		return (new);
	}
	return (NULL);
}
