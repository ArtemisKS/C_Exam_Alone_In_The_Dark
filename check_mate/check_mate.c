/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:03:48 by exam              #+#    #+#             */
/*   Updated: 2018/11/20 21:09:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static const char g_arr[5] = "QBRPH";

static int		det_fig_pos(char **par, int bs, char fig)
{
	int		i;
	int		j;

	i = -1;
	while ((j = -1) && par[++i])
		while (++j < bs)
			if (par[i][j] == fig)
				return (bs * i + j);
	return (-1);
}

int		ft_strlen(const char *str)
{
	int i;

	i = -1;
	while(str[++i])
		;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i] = 0;
	return (res);
}

int				is_in_arr(const char *arr, char c)
{
	int		i;

	i = -1;
	while (arr[++i])
		if (arr[i] == c)
			return (1);
	return (0);
}

static char		*fill_pf(char **par, int bs, int pf[], int s)
{
	int		i;
	int		j;
	int		ind;
	char	*fig;

	i = -1;
	ind = -1;
	fig = malloc(sizeof(char) * s);
	while (++i < s && !(fig[i] = 0))
		pf[i] = 0;
	i = -1;
	while ((j = -1) && par[++i])
		while (++j < bs)
			if (is_in_arr(g_arr, par[i][j]) && (fig[++ind] = par[i][j]))
				pf[ind] = bs * i + j;
	return (fig);
}

void				check_pawn(int pos, char **board, int bs, int size)
{
	int		i;
	int		j;

	i = pos / bs;
	j = pos % bs;
	if (i - 1 >= 0 && j - 1 >= 0)
		board[i - 1][j - 1] = '1';
	if (i + 1 < size && j - 1 >= 0)
		board[i + 1][j - 1] = '1';
	if (i - 1 >= 0 && j + 1 < bs)
		board[i - 1][j + 1] = '1';
	if (i + 1 < size && j + 1 < bs)
		board[i + 1][j + 1] = '1';
}

void				check_rook(int pos, char **board, int bs, int size)
{
	int		i;
	int		j;
	int		k;

	i = pos / bs;
	j = pos % bs;
	k = -1;
	while (++k < bs)
		board[i][k] = '1';
	k = -1;
	while (++k < size)
		board[k][j] = '1';
}

void				check_knight(int pos, char **board, int bs, int size)
{
	int				i;
	int				j;
	const int		l = 2;
	const int		sh = 1;

	i = pos / bs;
	j = pos % bs;
	if (i + sh < size && j + l < bs)
		board[i + sh][j + l] = '1';
	if (i - sh >= 0 && j + l < bs)
		board[i - sh][j + l] = '1';
	if (i + l < size && j + sh < bs)
		board[i + l][j + sh] = '1';
	if (i + l < size && j - sh >= 0)
		board[i + l][j - sh] = '1';
	if (i + sh < size && j - l >= 0)
		board[i + sh][j - l] = '1';
	if (i - sh >= 0 && j - l >= 0)
		board[i - sh][j - l] = '1';
	if (i - l >= 0 && j - sh >= 0)
		board[i - l][j - sh] = '1';
	if (i - l >= 0 && j + sh < bs)
		board[i - l][j + sh] = '1';
}

void				check_bishop(int pos, char **board, int bs, int size)
{
	int		i;
	int		j;
	int		ind;
	int		fl;

	i = pos / bs;
	j = pos % bs;
	ind = 0;
	fl = 1;
	while (fl && !(fl = 0))
	{
		board[i][j] = '1';
		if (j + ++ind < bs && i + ind < size && (fl = 1))
			board[i + ind][j + ind] = '1';
		if (j - ind >= 0 && i - ind >= 0 && (fl = 1))
			board[i - ind][j - ind] = '1';
		if (i - ind >= 0 && j + ind < bs && (fl = 1))
			board[i - ind][j + ind] = '1';
		if (i + ind < size && j - ind >= 0 && (fl = 1))
			board[i + ind][j - ind] = '1';
	}
}

void	check_mate(char **par, char **board, int size, int bs)
{
	int		i;
	int		kp;
	int		fp[size * 2];
	char	*fig;
	int		len;

	i = -1;
	fig = fill_pf(par, bs, fp, size * 2);
	len = ft_strlen(fig);
	kp = det_fig_pos(par, bs, 'K');
	while (++i < len)
	{
		if (fig[i] == 'Q')
		{
			check_bishop(fp[i], board, bs, size);
			check_rook(fp[i], board, bs, size);
		}
		else if (fig[i] == 'B')
			check_bishop(fp[i], board, bs, size);
		else if (fig[i] == 'R')
			check_rook(fp[i], board, bs, size);
		else if (fig[i] == 'H')
			check_knight(fp[i], board, bs, size);
		else if (fig[i] == 'P')
			check_pawn(fp[i], board, bs, size);
	}
	// for (i = 0; board[i]; i++)
	// 	printf("%s\n", board[i]);
	if (board[kp / bs][kp % bs] == '1')
		write(1, "Success", 7);
	else
		write(1, "Fail", 4);
}

int		main(int ac, char **av)
{
	int		i;
	char	**board;
	int		j;
	int		bs;

	i = 0;
	if (ac > 1)
	{
		bs = ft_strlen(av[1]);
		board = (char **)malloc(sizeof(char *) * ac);
		while (++i < ac && (j = -1))
		{
			board[i - 1] = malloc(bs + 1);
			while (++j < bs)
				board[i - 1][j] = '0';
			board[i - 1][j] = 0;
		}
		board[i - 1] = NULL;
		check_mate(av + 1, board, ac - 1, bs);
	}
	write(1, "\n", 1);
	return (0);
}
