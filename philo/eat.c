/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:42:55 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/18 09:35:15 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->check_mutex);
	if (!philo->data->check && !philo->data->one)
	{
		pthread_mutex_unlock(&philo->data->check_mutex);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = get_current_time_ms();
		pthread_mutex_unlock(&philo->meal_mutex);
		printing(2, philo);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->data->meals_to_eat)
		{
			pthread_mutex_lock(&philo->data->data_meal_counter_mutex);
			philo->data->meals++;
			pthread_mutex_unlock(&philo->data->data_meal_counter_mutex);
		}
		muslp(philo->data->t_e, philo);
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
	unlock_forks(philo);
}
