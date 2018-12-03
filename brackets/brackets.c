/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <exam@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:04:38 by exam              #+#    #+#             */
/*   Updated: 2018/10/16 11:34:11 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

const char ba[6] = {'(', '{', '[', ')', '}', ']'};
const int ia[6] = {-1, -2, -3, 1, 2, 3};

int is_in_arr(char c, const char *arr)
{
	int i = -1;

	while (arr[++i])
		if (arr[i] == c)
			return (i);
	return (-1);
}

int count_cor_brackets(const char *s)
{
	int i = -1;
	int cnt = 0;
	int ind = -1;

	while (s[++i])
		if ((ind = is_in_arr(s[i], ba)) != -1)
			cnt += ia[ind];
	return (cnt);
}

char *subst_brackets(char *s)
{
	int i = -1;
	int pi = 0;
	int prev = 0;
	int cnt = 0;
	int ind = -1;
	
	while (s[++i])
	{
		if ((ind = is_in_arr(s[i], ba)) != -1)
		{
			cnt = ia[ind];
			if (!(prev + cnt) && prev < 0)
			{
				s[pi] = ' ';
				s[i] = ' ';
			}
			prev = cnt;
			pi = i;
		}
		ind = -1;
	}
	return (s);
}

int brackets_num(char *s)
{
	int i = -1;
	int cnt = 0;
	
	while (s[++i])
		if (is_in_arr(s[i], ba) != -1)
			cnt++;
	return (cnt);
}

int brackets_are_fine(char *str)
{
	int bnum = 0;

	if (!brackets_num(str))
		return (1);
	if (count_cor_brackets(str))
		return (0);
	while ((bnum = brackets_num(str)))
	{
		str = subst_brackets(str);
		if (bnum == brackets_num(str))
			return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	int i = 0;

	if (ac > 1)
		while (++i < ac)
		{
			if (brackets_are_fine(av[i]))
				write(1, "OK\n", 3);
			else
				write(1, "Error\n", 6);
		}
	else
		write(1, "\n", 1);
}
