/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarqu <manmarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by manmarqu          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by manmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_over(philo->data))
	{
		philo_eat(philo);
		if (is_simulation_over(philo->data))
			break ;
		philo_sleep(philo);
		if (is_simulation_over(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

static int	check_death(t_data *data)
{
	int			i;
	long long	time_since_meal;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->state_mutex);
		time_since_meal = get_time_ms() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->state_mutex);
		if (time_since_meal > (long long)data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			pthread_mutex_lock(&data->state_mutex);
			data->simulation_over = 1;
			pthread_mutex_unlock(&data->state_mutex);
			write_death(&data->philos[i], data->start_time);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->meals_required == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (data->philos[i].meals_eaten < data->meals_required)
			all_ate = 0;
		pthread_mutex_unlock(&data->state_mutex);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->state_mutex);
		data->simulation_over = 1;
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

static void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_all_ate(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (1);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
		pthread_join(data->philos[i++].thread, NULL);
	return (0);
}
