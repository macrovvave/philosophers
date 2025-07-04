#include "philosophers.h"

void eat(t_philosopher* philo)
{
    if(philo->shared_data->check)
    {
        unlock_forks(philo);
        return ;
    }
    pthread_mutex_lock(&philo->meal_mutex);  // lock before writing
    philo->last_meal_time = get_current_time_ms();
    printf("[%ld]: %d is eating\n", get_elapsed_time(philo->shared_data->start), philo->id);
    precise_sleep(philo->shared_data->t_e);
    pthread_mutex_unlock(&philo->meal_mutex);
    philo->meals_eaten++;
    unlock_forks(philo);    

}