/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarqu <manmarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by manmarqu          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by manmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_valid_str(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi_strict(const char *str)
{
	long long	result;

	if (!is_valid_str(str))
		return (-1);
	result = 0;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > 2147483647)
			return (-1);
		str++;
	}
	return ((int)result);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 33), 1);
	data->num_philos = ft_atoi_strict(argv[1]);
	data->time_to_die = ft_atoi_strict(argv[2]);
	data->time_to_eat = ft_atoi_strict(argv[3]);
	data->time_to_sleep = ft_atoi_strict(argv[4]);
	data->meals_required = -1;
	if (argc == 6)
		data->meals_required = ft_atoi_strict(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (write(2, "Error: positive integers only\n", 30), 1);
	if (argc == 6 && data->meals_required <= 0)
		return (write(2, "Error: meals must be positive\n", 30), 1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork
			= &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	data->simulation_over = 0;
	data->start_time = get_time_ms();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	return (init_philos(data));
}
