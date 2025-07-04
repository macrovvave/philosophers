/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:59:21 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/30 09:30:57 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void think(t_philosopher* philo)
{
	if(philo->shared_data->check)
		return ;
	printf("[%ld]; %d is thinking\n", get_elapsed_time(philo->shared_data->start), philo->id);
}