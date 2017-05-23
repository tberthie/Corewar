/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gthomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:04:13 by gthomas           #+#    #+#             */
/*   Updated: 2017/05/16 13:31:47 by gthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			no_word(char *s, int i)
{
	if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',')
			++i;
	}
	else if (s[i] == '#')
	{
		while (s[i] != '\n' && s[i] != '\0')
			++i;
	}
	return (i);
}

int			nb_line(char *s, int i, int cnt)
{
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',' ||
				s[i] == '#')
			i = no_word(s, i);
		else if (s[i] == '"' && s[i] != '\0')
		{
			++i;
			cnt += 1;
			while (s[i] != '"' && s[i] != '\0')
				++i;
			++i;
		}
		else if (s[i] != '\0' && s[i] != '#')
		{
			cnt += 1;
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '"'
					&& s[i] != ',' && s[i] != '#' && s[i] != '\0')
				++i;
		}
	}
	return (cnt);
}

char		**nb_word(char *s, char **new, int i, int j)
{
	int		cnt;

	while (s[i])
	{
		cnt = 0;
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',' ||
				s[i] == '#')
			i = no_word(s, i);
		else if (s[i++] == '"' && (cnt = i))
		{
			while (s[i] != '"' && s[i] != '\0')
				++i;
			ft_m((void **)(&new[j++]), (cnt = ++i - cnt));
		}
		else if (s[i] != '\0' && s[i] != '#' && (cnt = i))
		{
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '"'
					&& s[i] != ',' && s[i] != '#' && s[i] != '\0')
				++i;
			ft_m((void **)(&new[j++]), (cnt = i - cnt));
		}
	}
	ft_m((void **)(&new[j]), 1);
	return (new);
}

char		**split(char *s, char **new, int j, int i)
{
	int		k;

	while (s[i])
	{
		k = 0;
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',' ||
				s[i] == '#')
			i = no_word(s, i);
		else if (s[i] == '"')
		{
			new[j][k++] = s[i++];
			while (s[i] != '"' && s[i] != '\0')
				new[j][k++] = s[i++];
			new[j][k] = s[i++];
			new[j++][k + 1] = '\0';
		}
		else if (s[i] != '\0' && s[i] != '#')
		{
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '"'
					&& s[i] != ',' && s[i] != '#' && s[i] != '\0')
				new[j][k++] = s[i++];
			new[j++][k] = '\0';
		}
	}
	return (new);
}

char		**ft_splitws(char *str)
{
	char	**new;
	int		lines;

	new = NULL;
	if (str)
	{
		lines = nb_line(str, 0, 0);
		if (!(new = (char **)malloc((lines + 1) * (sizeof(char *)))))
			return (NULL);
		new = nb_word(str, new, 0, 0);
		new = split(str, new, 0, 0);
		new[lines] = NULL;
	}
	return (new);
}
