/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:42:55 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/17 17:35:26 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared_data->check_mutex); // 2.0 lock
	if (!philo->shared_data->check && !philo->shared_data->one)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex); // 2.1 unlock
		pthread_mutex_lock(&philo->meal_mutex); // 3.0 lock 
		philo->last_meal_time = get_current_time_ms();
		pthread_mutex_unlock(&philo->meal_mutex); // 3.0 unlock
		printing(2, philo);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->shared_data->meals_to_eat)
		{
			pthread_mutex_lock(&philo->shared_data->data_meal_counter_mutex); // 4.0 lock 
			philo->shared_data->meals++;
			pthread_mutex_unlock(&philo->shared_data->data_meal_counter_mutex); // 4.0 unlock 
		}
		ft_usleep(philo->shared_data->t_e, philo);
		unlock_forks(philo); // changed the place of the unforking
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex); //. 2.2 unlock 
	unlock_forks(philo);
}
