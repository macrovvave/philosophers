#include "philosophers.h"

void eat(t_philosopher* philo)
{
	pthread_mutex_lock(&philo->meal_mutex);  // lock before writing
    philo->last_meal_time = get_current_time_ms();
    pthread_mutex_unlock(&philo->meal_mutex);
    
    printf("%d %d is eating\n", get_elapsed_time(philo->shared_data->start), philo->id);
    precise_sleep(philo->shared_data->t_e);
    
    philo->meals_eaten++;
}