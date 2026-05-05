/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarqu <manmarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by manmarqu          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by manmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		while (!is_simulation_over(philo->data))
			usleep(200);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->state_mutex);
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	long long	think_time;

	print_status(philo, "is thinking");
	think_time = philo->data->time_to_die
		- philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 600)
		think_time = 200;
	smart_sleep(think_time / 2, philo->data);
}
