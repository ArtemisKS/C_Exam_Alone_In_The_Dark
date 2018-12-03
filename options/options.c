/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:28:35 by exam              #+#    #+#             */
/*   Updated: 2018/12/03 07:57:14 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

const char g_arr[26] = "abcdefghijklmnopqrstuvwxyz";

int		ft_strlen(const char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int		is_in_arr(const char *arr, char c, int *ind)
{
	int		i;

	i = -1;
	while (arr[++i])
		if (arr[i] == c)
		{
			*ind = i;
			return (1);
		}
	return (0);
}

int		validate(const char *str, int *usage, int *invalid)
{
	int		i;
	int		ind;

	i = 0;
	ind = 0;
	if (str[0] && str[1] && str[0] == '-' && str[1] == 'h')
		*usage = 1;
	else
		while (str[++i])
			if (!is_in_arr(g_arr, str[i], &ind))
				*invalid = 1;
	if (*invalid || *usage)
		return (0);
	return (1);
}

void	assign_options(const char *str, int *options, int print)
{
	int		ind;
	int		i;
	char	c;
	int		bit;

	ind = -1;
	i = 0;
	if (str[i] != '-')
		return ;
	while (str[++i])
	{
		is_in_arr(g_arr, str[i], &ind);
		*options |= (1 << ind);
	}
	if (print && (i = 32))
	{
		while (--i >= 0)
		{
			bit = (*options >> i) & 1;
			c = bit + '0';
			write(1, &c, 1);
			(i % 8 == 0 && i) ? write(1, " ", 1) : 1;
		}
		write(1, "\n", 1);
	}
}

int		main(int ac, char **av)
{
	int		i;
	int		usage;
	int		invalid;
	int		options;

	i = 0;
	usage = 0;
	options = 0;
	invalid = 0;
	if (ac == 1)
		write(1, "options: abcdefghijklmnopqrstuvwxyz\n", 36);
	else
	{
		while (++i < ac)
			if (av[i][0] == '-' && !validate(av[i], &usage, &invalid))
				break ;
		if (!(i = 0) && !usage && !invalid)
			while (++i < ac)
				assign_options(av[i], &options, i == ac - 1);
		else if (usage)
			write(1, "options: abcdefghijklmnopqrstuvwxyz\n", 36);
		else
			write(1, "Invalid Option\n", 15);
	}
	return (0);
}
