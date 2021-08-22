/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 07:58:23 by gpaul             #+#    #+#             */
/*   Updated: 2021/08/22 16:02:32 by gpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

static int	nb_char(int nbr, char *base)
{
	unsigned int	nb_base;
	unsigned int	nb;
	int				car;

	car = 0;
	nb = nbr;
	nb_base = ft_strlen(base);
	if (check_base(base) == 0)
	{
		if (nbr < 0)
		{
			nb = -nbr;
			car++;
		}
		while (nb != 0)
		{
			nb = nb / nb_base;
			car++;
		}
	}
	return (car);
}

static char	*ft_putnbr_base(int nbr, char *base, char *res, int *i)
{
	unsigned int	nb_base;
	unsigned int	nb;

	nb = nbr;
	nb_base = ft_strlen(base);
	if (check_base(base) == 0)
	{
		if (nbr < 0)
		{
			res[*i] = ('-');
			(*i)++;
			nb = -nbr;
		}
		if (nb >= nb_base)
		{
			ft_putnbr_base(nb / nb_base, base, res, i);
			(*i)++;
		}
		res[*i] = (base[nb % nb_base]);
		return (res);
	}
	return (0);
}

static char	*ft_premier_base(char *base_to)
{
	char	*conv;

	conv = malloc(sizeof(char) * 2);
	if (conv == NULL)
		return (NULL);
	conv[0] = base_to[0];
	conv[1] = '\0';
	return (conv);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		res;
	char	*conv;
	int		len;
	int		*p_i;
	int		i;

	if (check_base(base_from) == 0 && check_base(base_to) == 0)
	{
		res = ft_atoi_base(nbr, base_from, base_to);
		if (res == 0)
			return (ft_premier_base(base_to));
		(conv = malloc(sizeof(char) * (nb_char(res, base_to) + 1)));
		i = 0;
		p_i = &i;
		conv = ft_putnbr_base(res, base_to, conv, p_i);
		len = nb_char(res, base_to);
		conv[len] = '\0';
	}
	else
		return (NULL);
	return (conv);
}
