/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:36:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/15 19:26:16 by macroooowav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(char *txt, long time, t_philosopher *philo, int n)
{
	pthread_mutex_lock(&philo->shared_data->print);
	if (!n && !philo->shared_data->check)
	{
		printf("[%ld]: ", time);
		printf("%d ", philo->id);
		printf("%s\n", txt);
	}
	else if (n && !philo->shared_data->check)
	{
		printf("[%ld]: ", time);
		printf("%s\n", txt);
	}
	pthread_mutex_unlock(&philo->shared_data->print);
}

int	check_values(t_data *data)
{
	if (data->p_n > 200)
	{
		printf("number of philosophers must be at most 200, try again.\n");
		free(data);
		return (0);
	}
	if (data->t_d < 60 || data->t_e < 60 || data->t_s < 60)
	{
		printf("time to die, eat, sleep, must at least be 60ms, try again.\n");
		free(data);
		return (0);
	}
	return (1);
}

long long	ft_atoi(char *num, long long *var)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (num[i])
	{
		if (!(num[i] >= '0' && num[i] <= '9'))
			return (0);
		result = result * 10 + (num[i] - 48);
		i++;
	}
	*var = result;
	return (result);
}

int	should_die(t_philosopher *philo)
{
	long long	t_d;

	t_d = philo->shared_data->t_d;
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_current_time_ms() - philo->last_meal_time > t_d)
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
	pthread_mutex_lock(&philo->shared_data->data_meal_counter_mutex);
	if (philo->shared_data->meals_to_eat <= 0)
		return (0);
	if (philo->shared_data->meals >= philo->shared_data->p_n)
	{
		pthread_mutex_unlock(&philo->shared_data->data_meal_counter_mutex);
		printing(4, philo);
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = true;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared_data->data_meal_counter_mutex);
	return (0);
}
