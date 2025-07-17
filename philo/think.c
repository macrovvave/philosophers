/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:59:21 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/17 22:05:02 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philo)
{
// 	long long	t_d;
// 	long long	t_s;
// 	long long	t_e;

// 	t_d = philo->shared_data->t_d;
// 	t_s = philo->shared_data->t_s;
// 	t_e = philo->shared_data->t_e;
// 	if (philo->id % 2 == 0 && philo->shared_data->p_n > 1)
// 			ft_usleep((t_s + t_e - t_d), philo);
	pthread_mutex_lock(&philo->shared_data->check_mutex); // 10.0 lock
	if (!philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex); // 10.1 unlock
		
		printing(5, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex); // 10.2 unlock
}
