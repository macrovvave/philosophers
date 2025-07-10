#include "philosophers.h"


void lock_forks(t_philosopher* philo )
{
    pthread_mutex_lock(&philo->shared_data->forks[philo->left_fork_id]);
    if (philo->shared_data->one == false)
        pthread_mutex_lock(&philo->shared_data->forks[philo->right_fork_id]);
    pthread_mutex_lock(&philo->shared_data->check_mutex);
    if (!philo->shared_data->check)
    {
        pthread_mutex_unlock(&philo->shared_data->check_mutex);
        pthread_mutex_lock(&philo->shared_data->printing_mutex);
    	if (!philo->shared_data->one)
            printf("[%ld]: %d has taken two forks\n", (get_current_time_ms() - philo->shared_data->start), philo->id);
        else
            printf("[%ld]: %d has taken one fork\n", (get_current_time_ms() - philo->shared_data->start), philo->id);
        pthread_mutex_unlock(&philo->shared_data->printing_mutex);
    }
    else
        pthread_mutex_unlock(&philo->shared_data->check_mutex);
}

void unlock_forks(t_philosopher* philo )
{
    if (!philo->shared_data->one)
        pthread_mutex_unlock(&philo->shared_data->forks[philo->right_fork_id]);
    pthread_mutex_unlock(&philo->shared_data->forks[philo->left_fork_id]);
}