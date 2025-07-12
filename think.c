/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:59:21 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/12 21:48:30 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared_data->check_mutex);
	if (philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
	printing(5, philo);
}
