/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:23:21 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:30 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->shared_data;
	while (philo->meals_eaten < data->meals_to_eat || data->meals_to_eat == -1)
	{
		pthread_mutex_lock(&data->check_mutex);
		if (data->check)
		{
			pthread_mutex_unlock(&data->check_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->check_mutex);
		lock_forks(philo);
		eat(philo);
		sleep_func(philo);
		think(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *)arg;
	while (!philo->shared_data->check)
	{
		i = 0;
		while (i < philo->shared_data->p_n)
		{
			if (should_die(&philo[i]))
				return (NULL);
			else if (ate_enough(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(400);
	}
	return (NULL);
}

// ./philo 3 120 60 60    
// [0]: 2 has taken two forks
// [0]: 2 is eating
// [60]: 2 is sleeping
// [60]: 1 has taken two forks
// [60]: 1 is eating
// [120]: 1 is sleeping
// [120]: 0 died
// [120]: 2 is thinking


void	threads_production(pthread_t *philos, t_philosopher *philo, int i)
{
	while (i < philo->shared_data->p_n)
	{
		pthread_create(&philos[i], NULL, routine, &philo[i]);
		i += 2;
	}
}

void	launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	threads_production(philos, philo_struct, 0);
	if (data->p_n > 1)
	{
		usleep(300);
		threads_production(philos, philo_struct, 1);
	}
	pthread_create(&monitor_thread, NULL, monitor, philo_struct);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->p_n)
		pthread_join(philos[i++], NULL);
}
