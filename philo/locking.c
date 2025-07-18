/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:44:46 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/18 09:39:05 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_forks(t_philosopher *philo )
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printing(6, philo);
	if (!philo->data->one)
	{
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		printing(6, philo);
	}
}

void	unlock_forks(t_philosopher *philo)
{
	if (!philo->data->one)
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
}
