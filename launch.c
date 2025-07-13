/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:23:17 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/13 16:40:42 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(int check, t_philosopher *philo)
{
	long long	start;

	pthread_mutex_lock(&philo->shared_data->check_mutex);
	start = philo->shared_data->start;
	if (check == 3 && !philo->shared_data->check)
		printf("[%ld]: %d died\n", el_time(start), philo->id);
	else if (check == 7 && !philo->shared_data->check)
		printf("[%ld]: %d has taken two forks\n", el_time(start), philo->id);
	else if (check == 1 && !philo->shared_data->check)
		printf("[%ld]: %d is sleeping\n", el_time(start), philo->id);
	else if (check == 2 && !philo->shared_data->check)
		printf("[%ld]: %d is eating\n", el_time(start), philo->id);
	else if (check == 6 && !philo->shared_data->check)
		printf("[%ld]: %d has taken one fork\n", el_time(start), philo->id);
	else if (check == 4 && !philo->shared_data->check)
		printf("[%ld]: all the philos ate their meals\n", el_time(start));
	else if (check == 5 && !philo->shared_data->check)
		printf("[%ld]: %d is thinking\n", el_time(start), philo->id);
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
}

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
