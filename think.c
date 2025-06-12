#include "philosophers.h"


void think(t_philosopher* philo)
{
	printf("%ld %d is thinking\n", get_elapsed_time(philo->shared_data->start), philo->id);
}