#include "philosophers.h"

void lock_forks(t_philosopher* philo )
{
    pthread_mutex_lock(&philo->left_fork_id);
    pthread_mutex_lock(&philo->right_fork_id);
    printf("%ld %d has taken two forks\n", get_elapsed_time(philo->shared_data->start), philo->id); // check if two msges are needed or only one
}

void unlock_forks(t_philosopher* philo )
{
    pthread_mutex_unlock(&philo->right_fork_id);
    pthread_mutex_unlock(&philo->left_fork_id);
}

  // lock before reading


void *monitor(void *arg)
{
    t_philosopher   *philo;
    t_data          *data;
    int i;
    long now;
    long since_last_meal;

    philo  = (t_philosopher*)arg;
    data = philo->shared_data;

    while (!data->check)
    {
        i = 0;
        while (i < data->p_n)
        {
            pthread_mutex_lock(&philo[i].meal_mutex); // Protect last_meal_time
            now = get_current_time_ms();
            since_last_meal = now - philo[i].last_meal_time;
            if (since_last_meal >= data->t_d)
            {
                data->check = true;
                pthread_mutex_unlock(&philo[i].meal_mutex);
                printf("%ld %d died\n", get_elapsed_time(data->start), philo[i].id);
                return (NULL);
            }
            pthread_mutex_unlock(&philo[i].meal_mutex);
            i++;
        }
        usleep(1000); // Slight delay to reduce CPU usage
    }
    return (NULL);
}


void* routine(void* arg)
{
    t_philosopher   *philo;
    t_data          *data;

    philo  = (t_philosopher*)arg;
    data = philo->shared_data;
    while (!data->check && (philo->meals_eaten < data->meals || data->meals == -1))
    {
        // Check death BEFORE trying to eat
        lock_forks(philo);  // Grab forks
        eat(philo);  // This updates meals_eaten
        unlock_forks(philo);
        sleep_func(philo);
        think(philo);
    }
    return NULL;
}

void launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data)
{
    int i = 0;
    pthread_t monitor_thread;
    
    pthread_create(&monitor_thread, NULL, monitor, philo_struct);
    // Create all threads
    while(i < data->p_n)
    {
        pthread_create(&philos[i], NULL, routine, &philo_struct[i]);
        
        i++;
    }
    pthread_join(monitor_thread, NULL);
    // Wait for all threads to finish
    i = 0;
    while(i < data->p_n)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
}

