/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:19:25 by staylan           #+#    #+#             */
/*   Updated: 2025/02/20 18:36:32 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (sign * result);
}

static void	send_signal(int id, char c)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		if ((c >> j) & 1)
			kill(id, SIGUSR1);
		else
			kill(id, SIGUSR2);
		j--;
		usleep(180);
	}
}

int	main(int argc, char **argv)
{
	int i = 0;
	if (argc == 3)
	{
		int server_id;
		server_id = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			send_signal(server_id, argv[2][i]);
			i++;
		}
	}
	else
		write(1, "The number of arguments must be three!", 39);
}