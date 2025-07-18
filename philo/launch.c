/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:33:09 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/18 11:44:33 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(int check, t_philosopher *philo)
{
	long long	start;

	pthread_mutex_lock(&philo->data->check_mutex);
	start = philo->data->start;
	if (check == 3 && !philo->data->check)
		ft_print("deid", el_time(start), philo, 0);
	else if (check == 7 && !philo->data->check)
		ft_print("has taken two forks", el_time(start), philo, 0);
	else if (check == 1 && !philo->data->check)
		ft_print("is sleeping", el_time(start), philo, 0);
	else if (check == 2 && !philo->data->check)
		ft_print("is eating", el_time(start), philo, 0);
	else if (check == 6 && !philo->data->check)
		ft_print("has taken a fork", el_time(start), philo, 0);
	else if (check == 4 && !philo->data->check)
		ft_print("all the philos ate their meals", el_time(start), philo, 1);
	else if (check == 5 && !philo->data->check)
		ft_print("is thinking", el_time(start), philo, 0);
	pthread_mutex_unlock(&philo->data->check_mutex);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;
	long			t_se;

	philo = (t_philosopher *)arg;
	data = philo->data;
	t_se = philo->data->t_s + philo->data->t_e;
	while ((philo->meals_eaten < data->meals_to_eat)
		|| data->meals_to_eat == -1)
	{
		pthread_mutex_lock(&data->check_mutex);
		if (data->check)
		{
			pthread_mutex_unlock(&data->check_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->check_mutex);
		lock_forks(philo);
		eat(philo);
		sleep_func(philo);
		think(philo);
		if (philo->data->p_n % 2 != 0)
			muslp(philo->data->t_d - t_se, philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *)arg;
	while (!philo->data->check)
	{
		i = 0;
		while (i < philo->data->p_n)
		{
			if (should_die(&philo[i]))
				return (NULL);
			else if (ate_enough(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(200);
	}
	return (NULL);
}

void	threads_production(pthread_t *philos, t_philosopher *philo, int i)
{
	while (i < philo->data->p_n)
	{
		pthread_create(&philos[i], NULL, routine, &philo[i]);
		i += 2;
	}
}

void	launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	threads_production(philos, philo_struct, 0);
	if (data->p_n > 1)
	{
		usleep(200);
		threads_production(philos, philo_struct, 1);
	}
	pthread_create(&monitor_thread, NULL, monitor, philo_struct);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->p_n)
		pthread_join(philos[i++], NULL);
}
