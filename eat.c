#include "philosophers.h"

void eat(t_philosopher* philo)
{
    pthread_mutex_lock(&philo->shared_data->check_mutex);
    if(philo->shared_data->check || philo->shared_data->one)
    {
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
        unlock_forks(philo);
        return ;
    }
	pthread_mutex_unlock(&philo->shared_data->check_mutex);
    printf("[%ld]: %d is eating\n", (get_current_time_ms() - philo->shared_data->start), philo->id);
    pthread_mutex_lock(&philo->meal_mutex);  // lock before writing
    philo->last_meal_time = get_current_time_ms();
    philo->meals_eaten++;
    if (philo->meals_eaten == philo->shared_data->meals_to_eat)
        philo->shared_data->meals++;
    pthread_mutex_unlock(&philo->meal_mutex);
	// pthread_mutex_lock(&philo->shared_data->printing_mutex);
    // pthread_mutex_unlock(&philo->shared_data->printing_mutex);

    ft_usleep(philo->shared_data->t_e);

    unlock_forks(philo);    
}