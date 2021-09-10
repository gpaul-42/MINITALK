/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 02:40:43 by gpaul             #+#    #+#             */
/*   Updated: 2021/09/10 03:08:04 by gpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

int	g_received;

static int	wait_sig(void)
{
	while (g_received == 0)
		usleep(10);
	if (g_received == 1)
		g_received = 0;
	return (1);
}

static void	handler(int signum)
{
	(void)signum;
	ft_putstr_fd("signal received\n", 1);
	g_received = 1;
}

static int	send_ascii(pid_t pid, char c)
{
	char	*tmp;
	char	*send;
	int		i;

	tmp = ft_itoa(c);
	send = ft_convert_base(tmp, "0123456789", "01");
	free(tmp);
	i = 0;
	if (ft_strlen(send) == 6)
	{
		kill(pid, SIGUSR2);
		wait_sig();
	}
	while (send[i])
	{
		if (send[i] == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		wait_sig();
	}
	free(send);
	return (0);
}

static void	pre_send(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		signal(SIGUSR2, handler);
		send_ascii(pid, str[i]);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		kill(pid, SIGUSR1);
		wait_sig();
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("The client need the pid and a string\n", 1);
		exit(EXIT_FAILURE);
	}
	else
		pre_send(atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
