#include "philosophers.h"

void    ft_usleep(long duration)
{
    long start;

    start = get_current_time_ms();
    while (true)
    {
        if (get_current_time_ms() - start >= duration)
            return ;
        usleep (400);
    }
}

void sleep_func(t_philosopher* philo)
{
	pthread_mutex_lock(&philo->shared_data->check_mutex);
    if(philo->shared_data->check)
    {
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
        unlock_forks(philo);
        return ;
    }
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
	printing(1, philo);
    ft_usleep(philo->shared_data->t_s);
}

//  split duration sleep into const chunks of time like ~500