#include "philosophers.h"



void* routine(void* arg) {
    t_philosopher* philo = (t_philosopher*)arg;
    t_data *data = philo->shared_data;  // Get data from philo struct
    
    while (1) {
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        pthread_mutex_lock(&data->forks[philo->right_fork_id]);
        eat(philo);
        pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
        sleep_func(philo);
        think(philo);
    }
}

void launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data)
{
    int i = 0;
    
    // Create all threads
    while(i < data->p_n)
    {
        pthread_create(&philos[i], NULL, routine, &philo_struct[i]);
        i++;
    }
    
    // Wait for all threads to finish
    i = 0;
    while(i < data->p_n)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
}