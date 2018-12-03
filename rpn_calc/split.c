/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <exam@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:41:39 by exam              #+#    #+#             */
/*   Updated: 2018/11/27 13:33:57 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"

static int	count_words(char *str, char c)
{
	int		i;
	int		cnt;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			cnt++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cnt);
}

int			ft_strlen(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

char		*ft_strsub(char *str, int st, int end)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * (end - st + 1));
	while (str[st] && st < end)
		res[i++] = str[st++];
	res[i] = 0;
	return (res);
}

static char	*get_word(char *str, char c, int n)
{
	int		i;
	int		cnt;
	int		j;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			cnt++;
		if (cnt == n)
			j = i;
		while (str[i] && str[i] != c)
			i++;
		if (cnt == n)
			return (ft_strsub(str, j, i));
	}
	return (NULL);
}

char		**split(char *str, char c)
{
	int		n;
	int		i;
	char	**arr;

	i = -1;
	n = count_words(str, c);
	arr = (char **)malloc(sizeof(char *) * (n + 1));
	while (++i < n)
		arr[i] = get_word(str, c, i + 1);
	arr[i] = NULL;
	return (arr);
}
