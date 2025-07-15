/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:44:46 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/15 18:11:06 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_forks(t_philosopher *philo )
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->shared_data->forks[philo->l_fork]);
		if (philo->shared_data->one == false)
			pthread_mutex_lock(&philo->shared_data->forks[philo->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->shared_data->forks[philo->r_fork]);
		if (philo->shared_data->one)
			pthread_mutex_lock(&philo->shared_data->forks[philo->l_fork]);
	}
	pthread_mutex_lock(&philo->shared_data->check_mutex);
	if (!philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		pthread_mutex_lock(&philo->print);
		if (!philo->shared_data->one)
			printing(7, philo);
		else
			printing(6, philo);
		pthread_mutex_unlock(&philo->print);
	}
	else
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
}

void	unlock_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!philo->shared_data->one)
			pthread_mutex_unlock(&philo->shared_data->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->shared_data->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared_data->forks[philo->r_fork]);
		if (philo->shared_data->one)
			pthread_mutex_unlock(&philo->shared_data->forks[philo->l_fork]);
	}
}
