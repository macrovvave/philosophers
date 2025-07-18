/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:59:21 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/18 09:40:34 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->check_mutex);
	if (!philo->data->check)
	{
		pthread_mutex_unlock(&philo->data->check_mutex);
		printing(5, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
}
