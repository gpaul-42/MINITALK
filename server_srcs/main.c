/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:13:09 by gpaul             #+#    #+#             */
/*   Updated: 2021/08/22 16:01:08 by gpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

static unsigned long int	check_char(char *cpy)
{
	char	*tmp;
	int		check;

	tmp = ft_convert_base(cpy, "01", "0123456789");
	check = ft_atoi(tmp);
	free(tmp);
	if (check >= 32 && check <= 127)
		return (check);
	else
		return (-1);
}

static void	handler(int signum)
{
	static char			cpy[8];
	static int			i;
	static int			n;
	static char			buffer[100];

	if (signum == 30)
		cpy[i++] = '1';
	else if (signum == 31)
		cpy[i++] = '0';
	if (i == 7)
	{
		if (check_char(cpy) == 127 || n == 99)
		{
			write(1, buffer, n);
			ft_memset(buffer, '\0', 99);
			n = 0;
		}
		buffer[n] = check_char(cpy);
		n++;
		i = 0;
		ft_memset(cpy, '\0', 7);
	}
}

int	main(void)
{
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (42)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
	}
	return (0);
}
