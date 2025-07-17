/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:56:16 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/17 21:54:38 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

t_data	*parse_args(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!ft_atoi(argv[4], &data->t_s) || !ft_atoi(argv[3], &data->t_e)
		|| !ft_atoi(argv[2], &data->t_d) || !ft_atoi(argv[1], &data->p_n))
		return (free(data), NULL);
	if (argc == 6)
	{
		if (!ft_atoi(argv[5], &data->tmp))
			return (free(data), NULL);
		data->meals_to_eat = (int)data->tmp;
	}
	else
		data->meals_to_eat = -1;
	data->one = true;
	if (data->p_n > 1)
		data->one = false;
	data->meals = 0;
	return (data);
}

int	forks_inis(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->check_mutex, NULL)
		|| pthread_mutex_init(&data->data_meal_counter_mutex, NULL)
		|| pthread_mutex_init(&data->sleep, NULL))
		return (0);
	return (1);
}

int	inis(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->p_n)
	{
		philo[i].id = i;
		if (i % 2 == 0)
		{
			philo[i].l_fork = i;
			philo[i].r_fork = (i + 1) % data->p_n;
		}
		else
		{
			philo[i].r_fork = i;
			philo[i].l_fork = (i + 1) % data->p_n;
			
		}
		philo[i].last_meal_time = get_current_time_ms();
		philo[i].meals_eaten = 0;
		philo[i].shared_data = data;
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&philo->shared_data->print, NULL))
		return (0);
	data->check = false;
	return (1);
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_t		*philosophers;
	t_philosopher	*philo_structs;

	data = parse_args(ac, av);
	if (!data)
	{
		printf("philo: invalid argument, try again.\n");
		return (0);
	}
	if (!check_values(data))
		return (0);
	else
	{
		data->start = get_current_time_ms();
		philosophers = malloc(sizeof(pthread_t) * data->p_n);
		data->forks = malloc(sizeof(pthread_mutex_t) * data->p_n);
		philo_structs = malloc(sizeof(t_philosopher) * data->p_n);
		if (!philosophers || !data->forks || !philo_structs)
			return (cleanup(data, philo_structs, philosophers), 0);
	}
	if (inis(data, philo_structs)
		&& forks_inis(data))
		launch(philosophers, philo_structs, data);
	cleanup(data, philo_structs, philosophers);
}
