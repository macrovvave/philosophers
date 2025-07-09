#include "philosophers.h"


void sleep_func(t_philosopher* philo)
{
    

	pthread_mutex_lock(&philo->shared_data->check_mutex);
    if(philo->shared_data->check)
    {
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
        unlock_forks(philo);
        return ;
    }
	printf("[%ld]: %d is sleeping\n", (get_current_time_ms() - philo->shared_data->start), philo->id);
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
    usleep(philo->shared_data->t_s * 1000);
}