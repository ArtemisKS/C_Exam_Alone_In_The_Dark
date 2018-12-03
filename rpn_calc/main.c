/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:02:31 by exam              #+#    #+#             */
/*   Updated: 2018/11/27 16:41:46 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"

#define IS_DIGIT(c)		(c >= '0' && c <= '9')

static const char g_op[5] = "+-*/%";

static int	calc_val(char *fns, char *sns, char op, int *fl)
{
	int			res;

	res = -1;
	if (op == '+')
		res = atoi(fns) + atoi(sns);
	else if (op == '-')
		res = atoi(fns) - atoi(sns);
	else if (op == '*')
		res = atoi(fns) * atoi(sns);
	else if (op == '/')
		(atoi(sns) == 0) ? (*fl = 1)
		: (res = atoi(fns) / atoi(sns));
	else if (op == '%')
		(atoi(sns) == 0) ? (*fl = 1)
		: (res = atoi(fns) % atoi(sns));
	else
		*fl = 1;
	return (res);
}

static char	**rewrite_arr(char **arr, int val, int ind, int *size)
{
	int		i;
	char	**tmp;
	int		ns;

	i = -1;
	ns = *size - 2;
	tmp = (char **)malloc(sizeof(char *) * (ns + 1));
	while (++i < ind)
		tmp[i] = arr[i];
	tmp[i] = ft_itoa(val);
	while (++i < ns && i + 2 < *size)
		tmp[i] = arr[i + 2];
	tmp[i] = NULL;
	*size = i;
	return (tmp);
}

static char	**eval_once(char **arr, int *size)
{
	int		i;
	int		val;
	int		fl;

	i = -1;
	fl = 0;
	while (arr[++i])
		if (is_in_arr(g_op, arr[i][0]) && !arr[i][1])
			break ;
	if (!arr[i] && !(arr[1] = NULL))
		return (arr);
	val = calc_val(arr[i - 2], arr[i - 1], arr[i][0], &fl);
	if (fl)
		return (NULL);
	arr = rewrite_arr(arr, val, i - 2, size);
	return (arr);
}

static int	is_valid(char **str)
{
	int		i;
	int		j;
	int		cnt;
	int		ncnt;

	i = -1;
	cnt = 0;
	ncnt = 0;
	while (str[++i] && (j = -1))
	{
		while (str[i][++j])
		{
			if (is_in_arr(g_op, str[i][j]) && !j)
				(!(str[i][j + 1] && IS_DIGIT(str[i][j + 1]))) ? cnt++ : 1;
			if ((str[i][0] == '-' && str[i][1] && IS_DIGIT(str[i][1]))
				|| (IS_DIGIT(str[i][j]) && !is_in_arr(g_op, str[i][0])))
				(!j) ? ncnt++ : 1;
			if (is_in_arr(g_op, str[i][j]) && j)
				return (0);
			if (!is_in_arr(g_op, str[i][j]) && !IS_DIGIT(str[i][j])
				&& str[i][j] != ' ')
				return (0);
		}
	}
	return (ncnt != cnt + 1) ? (0) : (1);
}

int			main(int ac, char **av)
{
	char	**arr;
	int		size;

	if (ac == 2 && (arr = split(av[1], ' ')))
	{
		if (!is_valid(arr))
			printf("Error\n");
		else
		{
			size = ft_arrlen(arr);
			while (arr[1])
				if (!(arr = eval_once(arr, &size)))
				{
					printf("Error\n");
					return (0);
				}
			printf("%s\n", arr[0]);
		}
	}
	else
		printf("Error\n");
	return (0);
}
