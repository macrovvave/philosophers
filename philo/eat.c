/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:42:55 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/15 19:38:48 by macroooowav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared_data->check_mutex);
	if (!philo->shared_data->check && !philo->shared_data->one)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		printing(2, philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = get_current_time_ms();
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->shared_data->meals_to_eat)
		{
			pthread_mutex_lock(&philo->shared_data->data_meal_counter_mutex);
			philo->shared_data->meals++;
			pthread_mutex_unlock(&philo->shared_data->data_meal_counter_mutex);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		ft_usleep(philo->shared_data->t_e, philo);
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
	unlock_forks(philo);
}
