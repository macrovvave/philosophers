/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:39:20 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/18 09:39:51 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	el_time(long start_time)
{
	return (get_current_time_ms() - start_time);
}

void	muslp(long long duration, t_philosopher *philo)
{
	long long	end_time;

	end_time = get_current_time_ms() + duration;
	while (get_current_time_ms() < end_time)
	{
		pthread_mutex_lock(&philo->data->check_mutex);
		if (philo->data->check)
		{
			pthread_mutex_unlock(&philo->data->check_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->check_mutex);
		usleep(100);
	}
}

void	sleep_func(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->check_mutex);
	if (!philo->data->check)
	{
		pthread_mutex_unlock(&philo->data->check_mutex);
		printing(1, philo);
		muslp(philo->data->t_s, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
}
