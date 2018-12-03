/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <exam@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:22:41 by exam              #+#    #+#             */
/*   Updated: 2018/11/27 13:33:39 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"

static int	calc_len(int val)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (!val)
		return (1);
	else if (val < 0)
		len++;
	while (val && ++len)
		val /= 10;
	return (len);
}

int			is_in_arr(const char *arr, char c)
{
	int		i;

	i = -1;
	while (arr[++i])
		if (arr[i] == c)
			return (1);
	return (0);
}

int			ft_arrlen(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

char		*ft_itoa(int val)
{
	int		i;
	int		len;
	char	*res;
	int		tmp;

	len = calc_len(val);
	res = malloc(sizeof(char) * (len + 1));
	i = len;
	res[i] = 0;
	if (!val && (res[--i] = '0'))
		return (res);
	if (val < 0)
		val *= -1;
	while ((tmp = val) && i--)
	{
		val /= 10;
		res[i] = (tmp - val * 10) + '0';
	}
	if (i)
		res[--i] = '-';
	return (res);
}
