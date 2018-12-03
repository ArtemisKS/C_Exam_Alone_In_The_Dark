/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <exam@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:03:50 by exam              #+#    #+#             */
/*   Updated: 2018/11/27 13:26:17 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_CALC_H
# define RPN_CALC_H

# include <stdlib.h>
# include <stdio.h>

char	*ft_strsub(char *s, int i, int j);
int		ft_strlen(char *s);
int		ft_arrlen(char **arr);
char	**split(char *s, char c);
char	*ft_itoa(int val);
int		is_in_arr(const char *arr, char c);

#endif
