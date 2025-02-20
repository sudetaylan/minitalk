/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:19:37 by staylan           #+#    #+#             */
/*   Updated: 2025/02/20 18:00:06 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putpid(int s)
{
	char	i;

	i = 0;
	if (s > 9)
	{
		ft_putpid(s / 10);
		ft_putpid(s % 10);
	}
	else
	{
		i = s + 48;
		write(1, &i, 1);
	}
}

static void	handle_signal(int signal)
{
	static char	c;
	static int	i;


	i++;
	if (signal == SIGUSR1)
		c = c | 1;
	else if (signal == SIGUSR2)
	{
		c = c | 0;
	}
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	c = c << 1;
}

int	main(void)
{
	int server_id;

	server_id = getpid();
	ft_putpid(server_id);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}