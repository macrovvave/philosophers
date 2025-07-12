/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:33:35 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/12 21:35:03 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
