/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:36:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/13 03:21:33 by macroooowav      ###   ########.fr       */
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

long long	ft_atoi(char *num, long long *var)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (num[i])
	{
		if (!(num[i] >= '0' && num[i] <= '9'))
			return (0);
		result = result * 10 + (num[i] - 48);
		i++;
	}
	*var = result;
	return (result);
}

int	should_die(t_philosopher *philo)
{
	long long	t_d;

	t_d = philo->shared_data->t_d;
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_current_time_ms() - philo->last_meal_time >= t_d)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		printing(3, philo);
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = true;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	ate_enough(t_philosopher *philo)
{
	if (philo->shared_data->meals_to_eat <= 0)
		return (0);
	if (philo->shared_data->meals >= philo->shared_data->p_n)
	{
		printing(4, philo);
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = true;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		return (1);
	}
	return (0);
}
