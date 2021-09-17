/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:13:09 by gpaul             #+#    #+#             */
/*   Updated: 2021/09/10 03:00:55 by gpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

static unsigned int	check_char(char *cpy)
{
	char				*tmp;
	unsigned int		check;

	tmp = ft_convert_base(cpy, "01", "0123456789");
	check = (unsigned int)ft_atoi(tmp);
	free(tmp);
	if ((check >= 32 && check <= 127) || check == 10)
		return (check);
	else
		return (1);
}

static void	handler(int signum, siginfo_t *info, void *ucontext)
{
	static char			cpy[8];
	static int			i;
	static int			n;
	static char			buffer[100];

	(void) ucontext;
	if (signum == 10 || signum == 30)
		cpy[i++] = '1';
	else if (signum == 12 || signum == 31)
		cpy[i++] = '0';
	if (i == 7)
	{
		if (check_char(cpy) == 127 || n == 99)
		{
			write(1, buffer, n);
			ft_memset(&buffer[0], '\0', 100);
			n = 0;
		}
		buffer[n] = (char)check_char(cpy);
		n++;
		i = 0;
		ft_memset(&cpy[0], '\0', 8);
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{


	char c = 10;

	write(1, &c, 1);

	struct sigaction	sa;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (42)
		usleep(5);
	return (0);
}
