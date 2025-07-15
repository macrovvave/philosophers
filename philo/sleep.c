/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:33:35 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/15 16:37:59 by macroooowav      ###   ########.fr       */
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
	if (!philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		pthread_mutex_lock(&philo->print);
		printing(1, philo);
		pthread_mutex_unlock(&philo->print);
		ft_usleep(philo->shared_data->t_s, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
}
