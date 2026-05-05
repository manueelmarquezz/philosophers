/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarqu <manmarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by manmarqu          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by manmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				simulation_over;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	t_philo			*philos;
}	t_data;

/* init.c */
int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);

/* main.c */
void		cleanup(t_data *data);

/* time.c */
long long	get_time_ms(void);
void		smart_sleep(long long duration_ms, t_data *data);

/* actions.c */
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* monitor.c */
int			start_simulation(t_data *data);

/* utils.c */
void		print_status(t_philo *philo, char *status);
void		write_death(t_philo *philo, long long start_time);
int			is_simulation_over(t_data *data);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(const char *s);

#endif
