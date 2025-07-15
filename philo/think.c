/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:59:21 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/15 19:26:38 by macroooowav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philosopher *philo)
{
	long long	t_d;
	long long	t_s;
	long long	t_e;

	pthread_mutex_lock(&philo->shared_data->check_mutex);
	if (philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		printing(5, philo);
		if (philo->id % 2 == 0)
		{
			t_d = philo->shared_data->t_d;
			t_e = philo->shared_data->t_e;
			t_s = philo->shared_data->t_s;
			ft_usleep((t_e + t_s - t_d), philo);
		}
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
}
