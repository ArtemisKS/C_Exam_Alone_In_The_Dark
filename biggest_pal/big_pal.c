/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_pal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 10:04:11 by exam              #+#    #+#             */
/*   Updated: 2018/12/03 07:35:33 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static inline int		is_pal(const char *str, int beg, int end)
{
	int		i;
	int		j;

	i = beg;
	j = end;
	while (i < j)
	{
		if (str[i] != str[j])
			return (0);
		i++;
		j--;
	}
	return (1);
}

static inline void		find_palindrome(const char *str, int *beg, int *end)
{
	int			len;
	int			i;
	int			j;
	int			step;

	i = -1;
	len = 0;
	while (str[++i])
	{
		j = i - 1;
		step = -1;
		while (str[++j])
			if ((is_pal(str, i, j)) && (j - i > step))
			{
				step = j - i;
				if (j - i >= len)
				{
					len = step;
					*beg = i;
					*end = j;
				}
				j = i;
			}
	}
}

void					print_bpal(const char *str)
{
	int		ind;
	int		end;

	ind = -1;
	end = -1;
	find_palindrome(str, &ind, &end);
	if (ind != -1 && end != -1)
		write(1, &str[ind], end - ind + 1);
}

int						main(int ac, char **av)
{
	if (ac == 2)
		print_bpal(av[1]);
	write(1, "\n", 1);
	return (0);
}
