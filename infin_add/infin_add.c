/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infin_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:14:19 by exam              #+#    #+#             */
/*   Updated: 2018/12/03 07:08:52 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

void ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

char* rewrite_sm_s(char *s, int size)
{
	int j;
	int i;
	char *str = malloc(sizeof(char) * (size + 1));
	str[size] = 0;
	j = size - 1;
	i = ft_strlen(s) - 1;
	while (i >= 0)
		str[j--] = s[i--];
	while (j >= 0)
		str[j--] = '0';
	return (str);
}

char* rewrite_res(char *s, int size)
{
	int j;
	char *str = malloc(sizeof(char) * (size + 2));
	str[size + 1] = 0;
	j = size;
	while (j > 0)
	{
		str[j] = s[j - 1];
		j--;
	}
	str[0] = '0';
	return (str);
}

void rewrite(char **s1, char **s2, int size)
{
	int i = 0;
	while (i < size)
	{
		if ((*s1)[i] == '-')
			(*s1)[i] = '0';
		if ((*s2)[i] == '-')
			(*s2)[i] = '0';
		i++;
	}
}

int calc_cycle(int j, int *k, char *b_s, char *sm_s, char *res)
{
	int num = 0;
    int ost = 0;
	while (j >= 0)
	{
		num = (b_s[j] - '0') + (sm_s[j] - '0');
		num += ost;
		if (num <= 9)
		{
			res[--(*k)] = num + '0';
			ost = 0;
		}
		else
		{
			res[--(*k)] = (num % 10) + '0';
			ost = num / 10;
		}
		j--;
	}
	return (ost);
}

int str_same(char *s1, char* s2)
{
	int i = 0;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (i < ft_strlen(s1))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int calc_cycle_min(int j, int *k, char *b_s, char *sm_s, char *res)
{
    int num = 0;
    int ost = 0;
    while (j >= 0)
    {
        num = (b_s[j] - '0') - (sm_s[j] - '0');
        num -= ost;
        if (num >= 0)
        {
            res[--(*k)] = num + '0';
            ost = 0;
        }
        else
        {
            res[--(*k)] = (10 + num) + '0';
            ost = 1;
        }
        j--;
    }
    return (ost);
}

void rewrite_pos(char **s1, char **s2, int size)
{
	char *res1 = malloc(sizeof(char) * (size - 1));
	char *res2 = malloc(sizeof(char) * (size - 1));
	int j = size - 1;
	int i = size - 2;
	res1[j] = 0;
	res2[j] = 0;
	while (i >= 0)
	{
		if ((*s1)[j] == '-')
			res1[i] = '0';
		else
			res1[i] = (*s1)[j];
		res2[i--] = (*s2)[j--];
	}
	*s1 = res1;
	*s2 = res2;
}

int is_bigger(char *s1, char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (s1[i] - '0' > s2[i] - '0')
			return (1);
		else if (s2[i] - '0' > s1[i] - '0')
			return (-1);
		i++;
	}
	return (0);
}

char *rewrite_s_char(char *s, char c)
{
	int i = -1;
	int cnt = 0;

	while (s[++i] == c)
		cnt++;
	i = -1;
	while (s[++i + cnt])
		s[i] = s[i + cnt];
	s[i] = 0;
	return (s);
}

char *res_str(char *s1, char *s2)
{
	int b_len;
	char *sm_s = NULL;
	char *b_s = NULL;
	char *res;
	int j;
	int k;
	int ost = 0;
	int fl = 0;
	int count = 0;

	b_len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	if (ft_strlen(s1) >= ft_strlen(s2))
	{
		if (ft_strlen(s1) == ft_strlen(s2))
		{
			if (s1[0] != '-' && s2[0] != '-')
			{
				if (is_bigger(s1, s2) == 1)
				{
					b_s = s1;
					sm_s = s2;
				}
				else if (is_bigger(s1, s2) == -1)
				{
					b_s = s2;
					sm_s = s1;
				}
				else if (!(is_bigger(s1, s2)))
				{
					sm_s = s1;
					b_s = s2;
				}
			}
			else if (s1[0] == '-' && s2[0] == '-')
			{
				if (is_bigger(&s1[1], &s2[1]) == 1)
				{
                    b_s= s1;
                    sm_s = s2;
                }
				else if(is_bigger(&s1[1], &s2[1]) == -1)
				{
                    b_s= s2;
                    sm_s = s1;
                }
				else if(!(is_bigger(s1, s2)))
				{
                    sm_s = s1;
                    b_s= s2;
                }
			}
			else if (s1[0] == '-')
			{
				b_s = s2;
				sm_s = s1;
			}
			else if (s2[0] == '-')
			{
				b_s = s1;
				sm_s = s2;
			}
		}
		else if (ft_strlen(s1) > ft_strlen(s2))
		{
			b_s = s1;
			sm_s = s2;
		}
	}
	else if (ft_strlen(s1) < ft_strlen(s2))
	{
		sm_s = s1;
		b_s = s2;
	}
	res = malloc(sizeof(char) * (b_len + 1));
	k = b_len;
	res[k] = 0;
	j = b_len - 1;
	if (ft_strlen(s1) - ft_strlen(s2) == 1 && s1[0] == '-'
		&& s2[0] != '-' && (is_bigger(&s1[1], s2) == -1) && (fl = 1))
	{
		k--;
		s1 = rewrite_s_char(s1, '-');
		ost = calc_cycle_min(ft_strlen(s1) - 1, &k, s2, s1, res);
		res = rewrite_s_char(res, '0');
		return (res);
	}
	else if (ft_strlen(s2) - ft_strlen(s1) == 1 && s2[0] == '-'
		&& s1[0] != '-' && (is_bigger(&s2[1], s1) == -1) && (fl = 1))
	{
		k--;
		s2 = rewrite_s_char(s2, '-');
		ost = calc_cycle_min(ft_strlen(s1) - 1, &k, s1, s2, res);
		res = rewrite_s_char(res, '0');
		return (res);
	}
	else if (sm_s[0] == '-' && b_s[0] == '-')
		fl = 2;
	else if (sm_s[0] == '-' || b_s[0] == '-')
		fl = 1;
	if (!fl || fl == 2)
		sm_s = rewrite_sm_s(sm_s, b_len);
	if (fl == 2)
		b_s = rewrite_sm_s(b_s, b_len);
	if (!fl)
		ost = calc_cycle(j, &k, b_s, sm_s, res);
	else if (fl == 2)
	{
		rewrite(&sm_s, &b_s, b_len);
		ost = calc_cycle(j, &k, b_s, sm_s, res);
		if (res[0] != '0')
			res = rewrite_res(res, ft_strlen(res));
		if (res[0] == '0')
			res[0] = '-';
	}
	else if (fl == 1)
	{
		if (b_s[0] == '-')
			fl = 5;
		sm_s = rewrite_sm_s(sm_s, b_len);
		if (fl == 5)
		{
			rewrite_pos(&sm_s, &b_s, b_len);
			j--;
		}
		else
			rewrite(&sm_s, &b_s, b_len);
		 if (str_same(b_s, sm_s))
		 {
		 	res = (char *)malloc(2);
	    	res[0] = '0';
	    	res[1] = 0;
	    	ost = 0;
		 }
		 else
			ost = calc_cycle_min(j, &k, b_s, sm_s, res);
		if (fl == 5 && !str_same(b_s, sm_s))
		{
			res[--k] = '-';
			while (res[++k] == '0')
				count++;
			if (count)
			{
				res += count;
				*res = '-';
			}
		}
	}
	if (ost > 0 && fl != 1)
	{
		res = rewrite_res(res, ft_strlen(res));
		if (res[0] == '0')
			res[k] = ost + '0';
	}
	return (res);
}

int main(int ac, char **av)
{
	char *s;
	if (ac == 3)
	{
		s = res_str(av[1], av[2]);
		ft_putstr(s);
		write(1, "\n", 1);
	}
	return (0);
}
