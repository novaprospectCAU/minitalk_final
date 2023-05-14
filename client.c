/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:49:40 by byelee            #+#    #+#             */
/*   Updated: 2023/04/28 14:49:44 by byelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_signal(pid_t pid, int temp)
{
	if (temp == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
}

static void	send_newline(pid_t pid, int temp)
{
	char	newline;
	int		bit_idx;
	int		sleep_checker;

	newline = '\n';
	bit_idx = 0;
	while (bit_idx < 8)
	{
		temp = newline >> (7 - bit_idx) & 1;
		send_signal(pid, temp);
		sleep_checker = usleep(120);
		if (sleep_checker < 0)
			exit(1);
		bit_idx++;
	}
}

void	transmit_signal(pid_t pid, char *str, size_t len)
{
	size_t	byte_idx;
	int		bit_idx;
	int		temp;
	int		sleep_checker;

	byte_idx = 0;
	while (byte_idx < len)
	{
		bit_idx = 0;
		while (bit_idx < 8)
		{
			temp = (str[byte_idx] >> (7 - bit_idx) & 1);
			send_signal(pid, temp);
			sleep_checker = usleep(120);
			if (sleep_checker < 0)
				exit(1);
			bit_idx++;
		}
		byte_idx++;
	}
	send_newline(pid, temp);
}

int	error_output(int err_num)
{
	if (err_num == 0)
		ft_printf("Invalid input. I think you missed PID or input String.\n");
	else if (err_num == 1)
		ft_printf("invalid input, Your PID has gone beyond the boundary.\n");
	else
		ft_printf("Error : dynamic allocation error occurred\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*str;
	size_t	idx;
	size_t	str_length;
	pid_t	pid;

	if (argc != 3)
		return (error_output(0));
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid < 100 || pid > 99998)
		return (error_output(1));
	idx = 0;
	while (argv[2][idx])
		idx++;
	str_length = idx;
	str = argv[2];
	transmit_signal(pid, str, str_length);
	return (0);
}
