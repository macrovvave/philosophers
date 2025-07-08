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
	pthread_mutex_unlock(&philo->shared_data->check_mutex);

	printf("[%ld]: %d is sleeping\n", get_elapsed_time(philo->shared_data->start), philo->id);
    precise_sleep(philo->shared_data->t_s);    
}