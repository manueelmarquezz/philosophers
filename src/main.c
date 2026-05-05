/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarqu <manmarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by manmarqu          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by manmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	if (data->philos)
		free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
	{
		write(2, "Error: initialization failed.\n", 30);
		cleanup(&data);
		return (1);
	}
	if (start_simulation(&data))
	{
		write(2, "Error: thread creation failed.\n", 31);
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
