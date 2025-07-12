/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:11:07 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/12 17:18:16 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(int check, t_philosopher *philo)
{
	long	start;

	start = philo->shared_data->start;
	pthread_mutex_lock(&philo->shared_data->printing_mutex);
	if (check == 3)
		printf("[%ld]: %d died\n", el_time(start), philo->id);
	else if (check == 7)
		printf("[%ld]: %d has taken two forks\n", el_time(start), philo->id);
	else if (check == 1)
		printf("[%ld]: %d is sleeping\n", el_time(start), philo->id);
	else if (check == 2)
		printf("[%ld]: %d is eating\n", el_time(start), philo->id);
	else if (check == 6)
		printf("[%ld]: %d has taken one fork\n", el_time(start), philo->id);
	else if (check == 4)
		printf("[%ld]: all the philos ate their meals\n", el_time(start));
	else if (check == 5)
		printf("[%ld]: %d is thinking\n", el_time(start), philo->id);
	pthread_mutex_unlock(&philo->shared_data->printing_mutex);
}

long long	ft_atoi(char *str, long long *var)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	*var = result;
	return (*var);
}

int	should_die(t_philosopher *philo)
{
	long long	t_d;

	t_d = philo->shared_data->t_d;
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_current_time_ms() - philo->last_meal_time >= t_d)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		printing(3, philo);
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = true;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	ate_enough(t_philosopher *philo)
{
	if (philo->shared_data->meals_to_eat <= 0)
		return (0);
	if (philo->shared_data->meals >= philo->shared_data->p_n)
	{
		printing(4, philo);
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = true;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		return (1);
	}
	return (0);
}
