/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:25:59 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/12 17:26:53 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data, t_philosopher *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->p_n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (philos)
		free(philos);
	if (threads)
		free(threads);
	if (data)
		free(data);
}
