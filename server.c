/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysuliman <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-09 14:10:07 by ysuliman          #+#    #+#             */
/*   Updated: 2024-07-09 14:10:07 by ysuliman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	ft_converter(int *bits)
{
	int		i;
	char	c;

	i = 0;
	while (i < 8)
		c = (c << 1) | bits[i++];
	return (c);
}

void	signal_handler(int signum)
{
	static int	i = 0;
	static int	bits[8];
	char		c;

	if (signum == SIGUSR1)
		bits[i++] = 0;
	else if (signum == SIGUSR2)
		bits[i++] = 1;
	if (i == 8)
	{
		c = ft_converter(bits);
		write(1, &c, 1);
		ft_memset(bits, 0, 8);
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("SERVER pid : %d\n", getpid());
	ft_memset(&signal_received, 0, sizeof(signal_received));
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
	{
		usleep(200);
	}
	return (0);
}
