/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:27:12 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/12 17:29:08 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((ts.tv_sec * 1000L) + (ts.tv_nsec / 1000000L));
}

long	el_time(long start_time)
{
	return (get_current_time_ms() - start_time);
}

void	ft_usleep(long long duration, t_philosopher *philo)
{
	long long	end_time;

	end_time = get_current_time_ms() + duration;
	while (get_current_time_ms() < end_time)
	{
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		if (philo->shared_data->check)
		{
			pthread_mutex_unlock(&philo->shared_data->check_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		usleep(100);
	}
}

void	sleep_func(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared_data->check_mutex);
	if (philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
	printing(1, philo);
	ft_usleep(philo->shared_data->t_s, philo);
}
