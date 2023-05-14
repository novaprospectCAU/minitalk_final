/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:32 by byelee            #+#    #+#             */
/*   Updated: 2023/04/28 14:50:33 by byelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>
void	signal_handler(int sig)
{
	static char	output;
	static int	idx;
	char		temp;

	temp = 1;
	if (sig == SIGUSR1)
	{ 
		output = output | (temp << (7 - idx));
		idx++;
	} 
	else
	{
		idx++;
	}
	if (idx == 8)
	{
		printf("%d : printed!\n", output);
		write(1, &output, 1);
		output = 0;
		idx = 0;
	}
}

static int	sig_error(void)
{
	write(1, "Error occurred while receiving signals\n", 39);
	return (0);
}

int	main(void)
{
	int	printf_len;

	printf_len = ft_printf("server PID : %d\n", getpid());
	if (printf_len < 0)
	{
		write(1, "error during print.\n", 20);
		return (0);
	}
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
		return (sig_error());
	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
		return (sig_error());
	while (1)
		pause();
	return (0);
}
