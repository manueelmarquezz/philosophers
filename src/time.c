/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarqu <manmarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by manmarqu          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by manmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

void	smart_sleep(long long duration_ms, t_data *data)
{
	long long	start;
	long long	elapsed;

	start = get_time_ms();
	while (!is_simulation_over(data))
	{
		elapsed = get_time_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		if (duration_ms - elapsed > 2)
			usleep(500);
		else
			usleep(100);
	}
}
