#include "philosophers.h"


void sleep_func(t_philosopher* philo)
{
	if(philo->shared_data->check)
		return ;
	printf("[%ld]: %d is sleeping\n", get_elapsed_time(philo->shared_data->start), philo->id);
	precise_sleep(philo->shared_data->t_s);
}