

#include "philosophers.h"

void	printing(int check, t_philosopher *philo) // removed the check mutex
{
	long long	start;

	start = philo->shared_data->start;
	pthread_mutex_lock(&philo->shared_data->check_mutex); // 5.0 lock | add this instead of print mutex before each printing call, back to old version
	if (check == 3 && !philo->shared_data->check)
		ft_print("====================> died", el_time(start), philo, 0);
	else if (check == 7 && !philo->shared_data->check)
		ft_print("has taken two forks", el_time(start), philo, 0);
	else if (check == 1 && !philo->shared_data->check)
		ft_print("is sleeping", el_time(start), philo, 0);
	else if (check == 2 && !philo->shared_data->check)
		ft_print("is eating", el_time(start), philo, 0);
	else if (check == 6 && !philo->shared_data->check)
		ft_print("has taken a fork", el_time(start), philo, 0);
	else if (check == 4 && !philo->shared_data->check)
		ft_print("all the philos ate their meals", el_time(start), philo, 1);
	else if (check == 5 && !philo->shared_data->check)
		ft_print("is thinking", el_time(start), philo, 0);
	pthread_mutex_unlock(&philo->shared_data->check_mutex); // 5.0 unlock
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->shared_data;
	while ((philo->meals_eaten < data->meals_to_eat) || data->meals_to_eat == -1)
	{
		pthread_mutex_lock(&data->check_mutex); // 1 lock
		if (data->check)
		{
			pthread_mutex_unlock(&data->check_mutex); // 1 unlock
			break ;
		}
		pthread_mutex_unlock(&data->check_mutex); // 1.2 unlck
		lock_forks(philo);
		eat(philo);
		sleep_func(philo);
		think(philo);
		if (philo->shared_data->p_n % 2 != 0) // last update - recheck w/o later
			ft_usleep((philo->shared_data->t_s + philo->shared_data->t_e - philo->shared_data->t_d), philo);
	}
	return (NULL);
}
// search for last update | this test still fails "4 310 200 100"

void	*monitor(void *arg)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *)arg;
	while (!philo->shared_data->check)
	{
		i = 0;
		while (i < philo->shared_data->p_n)
		{
			if (should_die(&philo[i]))
				return (NULL);
			else if (ate_enough(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(300);
	}
	return (NULL);
}

void	threads_production(pthread_t *philos, t_philosopher *philo, int i)
{
	while (i < philo->shared_data->p_n)
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
