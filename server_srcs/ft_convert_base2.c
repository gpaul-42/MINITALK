/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 07:58:37 by gpaul             #+#    #+#             */
/*   Updated: 2021/08/22 16:02:24 by gpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

int	check_char (char c)
{
	if (c == '-' || c == '+' || c == '\t'
		|| c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	check_base(char *base)
{
	int	i;
	int	e;
	int	v;

	i = 0;
	v = 0;
	while (base[i] != '\0')
	{
		e = 0;
		if (check_char(base[i]) == 1)
			return (1);
		while (base[e])
		{
			if (i != e && base[i] == base[e] && base[i] != '\0'
				&& base[e] != '\0')
				return (1);
			e++;
		}
		i++;
		v++;
	}
	if (v > 1)
		return (0);
	return (1);
}

int	in_base_here(char str, char *base, int z)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (str == base[i] && z == 0)
			return (0);
		else if (str == base[i] && z != 0)
			return (i);
		i++;
	}
	return (1);
}

int	ft_next(char *str, int z)
{
	int	i;
	int	moins;

	i = 0;
	moins = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			moins++;
		i++;
	}
	if (z == 0)
		return (i);
	return (moins);
}

int	ft_atoi_base(char *str, char *base_from, char *base_to)
{
	int	i;
	int	nb_moins;
	int	res;
	int	nb_base;

	i = 0;
	nb_moins = 0;
	res = 0;
	nb_base = ft_strlen(base_from);
	i = ft_next(str, 0);
	nb_moins = ft_next(str, 1);
	if (check_base(base_from) == 0 && check_base(base_to) == 0)
	{
		while (in_base_here(str[i], base_from, 0) == 0)
		{
			res = (res * nb_base) + in_base_here(str[i], base_from, 1);
			i++;
		}
	}
	if (nb_moins % 2 == 0)
		return (res);
	return (-res);
}
