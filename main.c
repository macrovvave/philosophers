/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:56:16 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/10 04:20:36 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data *data(void)
{
	static t_data data;

	return (&data);
}

t_data *parse_args(int argc, char **argv)
{
    t_data *data;
 
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
    if(!(data->t_s = ft_atoi(argv[4])) || !(data->t_e = ft_atoi(argv[3])) 
		|| !(data->t_d = ft_atoi(argv[2])) || !(data->p_n = ft_atoi(argv[1])))
	{
		free(data);
		return (NULL);
	}
	if(argc == 6)
	{
		if(!(data->meals_to_eat = ft_atoi(argv[5])))
		{
			free(data);
			return (NULL);
		}
	}
    else
		data->meals_to_eat = -1;
    data->one = true;    
    if (data->p_n > 1)
        data->one = false;
    data->meals = 0;
    return data;
}

void forks_inis(t_data *data, t_philosopher *philo_structs, pthread_t *philosophers)
{
	int i;

	i = 0;
	while(i < data->p_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			cleanup(data, philo_structs, philosophers);
			exit(1);
		}
		i++;
	}
}

void inis(t_data *data, t_philosopher *philo, pthread_t *philosophers)
{
	int i;

	i = 0;
	while ( i < data->p_n)
	{
        philo[i].id = i;
        philo[i].left_fork_id = i;
        philo[i].right_fork_id = (i + 1) % data->p_n;
        philo[i].last_meal_time = get_current_time_ms();
        philo[i].meals_eaten = 0;
		philo[i].shared_data = data;
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL))
		{
			cleanup(data, philo, philosophers);
			exit(1);
		}
		i++;
    }
	if (pthread_mutex_init(&data->check_mutex, NULL) 
		|| pthread_mutex_init(&data->printing_mutex, NULL))
		{
			cleanup(data, philo, philosophers);
			exit(1);
		}
	data->check = false;
}


int main(int ac, char **av)
{
	t_data *data;
	pthread_t *philosophers;           // Thread array
	t_philosopher *philo_structs;     // Philosopher data array

	if ((ac != 5 && ac != 6) || !(data = parse_args(ac, av)))
		return (0);
	else
	{
		data->start = get_current_time_ms();
		philosophers = malloc(sizeof(pthread_t) * data->p_n);
		data->forks = malloc(sizeof(pthread_mutex_t) * data->p_n);
		philo_structs = malloc(sizeof(t_philosopher) * data->p_n);
		if (!philosophers || !data->forks || !philo_structs)
		{
			cleanup(data, philo_structs, philosophers);
			return (0);
		}
	}
	inis(data, philo_structs, philosophers);
	forks_inis(data, philo_structs, philosophers);
    // printf("td = %lld | ts = %lld | te = %lld \n\n", data->t_d, data->t_s, data->t_e);
	launch(philosophers, philo_structs, data);
	cleanup(data, philo_structs, philosophers);
}