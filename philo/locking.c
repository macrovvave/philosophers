/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:44:46 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/14 23:23:20 by macroooowav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_forks(t_philosopher *philo )
{
	if (philo->id % 2 == 0)	
	{
		pthread_mutex_lock(&philo->shared_data->forks[philo->left_fork_id]);
		if (philo->shared_data->one == false)
			pthread_mutex_lock(&philo->shared_data->forks[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&philo->shared_data->forks[philo->right_fork_id]);
		if (philo->shared_data->one)
			pthread_mutex_lock(&philo->shared_data->forks[philo->left_fork_id]);
	}
	pthread_mutex_lock(&philo->shared_data->check_mutex);
	if (!philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		if (!philo->shared_data->one)
			printing(7, philo);
		else
			printing(6, philo);
	}
	else
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
}

void	unlock_forks(t_philosopher *philo )
{
	if (!philo->shared_data->one)
		pthread_mutex_unlock(&philo->shared_data->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->shared_data->forks[philo->left_fork_id]);
}
