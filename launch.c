#include "philosophers.h"

// void lock_forks(t_philosopher* philo )
// {
//     if (!philo->shared_data->check)
//     {
//         pthread_mutex_lock(&philo->shared_data->forks[philo->left_fork_id]);
//         pthread_mutex_lock(&philo->shared_data->forks[philo->right_fork_id]);
//         if (!philo->shared_data->check)
//             printf("[%ld]: %d has taken two forks\n", get_elapsed_time(philo->shared_data->start), philo->id);
//         else if (philo->shared_data->check)
//             unlock_forks(philo);
//     }
// }

void lock_forks(t_philosopher* philo )
{
    pthread_mutex_lock(&philo->shared_data->forks[philo->left_fork_id]);
    pthread_mutex_lock(&philo->shared_data->forks[philo->right_fork_id]);

    // After both forks are locked, check if simulation has ended
    pthread_mutex_lock(&philo->shared_data->check_mutex);
    if (!philo->shared_data->check)
    {
        printf("[%ld]: %d has taken two forks\n",
               get_elapsed_time(philo->shared_data->start), philo->id);
    }
    else
    {
        pthread_mutex_unlock(&philo->shared_data->check_mutex);
        unlock_forks(philo);
        return;
    }
    pthread_mutex_unlock(&philo->shared_data->check_mutex);
}



void unlock_forks(t_philosopher* philo )
{
    pthread_mutex_unlock(&philo->shared_data->forks[philo->right_fork_id]);
    pthread_mutex_unlock(&philo->shared_data->forks[philo->left_fork_id]);
}

void* routine(void* arg)
{
    t_philosopher   *philo = (t_philosopher*)arg;
    t_data          *data = philo->shared_data;

    while ((philo->meals_eaten < data->meals_to_eat || data->meals_to_eat == -1))
    {
        // Before starting, check if simulation ended
        pthread_mutex_lock(&data->check_mutex);
        if (data->check)
        {
            pthread_mutex_unlock(&data->check_mutex);
            break;
        }
        pthread_mutex_unlock(&data->check_mutex);

        lock_forks(philo);

        // Re-check after locking forks
        pthread_mutex_lock(&data->check_mutex);
        if (data->check)
        {
            pthread_mutex_unlock(&data->check_mutex);
            unlock_forks(philo);
            break;
        }
        pthread_mutex_unlock(&data->check_mutex);

        eat(philo);
        sleep_func(philo);
        think(philo);

        // If you want to exit after meals, check here
        if (data->meals_to_eat != -1 && philo->meals_eaten >= data->meals_to_eat)
            break;
    }
    return NULL;
}

// void* routine(void* arg)
// {
//     t_philosopher   *philo;
//     t_data          *data;

//     philo  = (t_philosopher*)arg;
//     data = philo->shared_data;
//     while ((philo->meals_eaten < data->meals_to_eat || data->meals_to_eat == -1))
//     {
//         pthread_mutex_lock(&data->check_mutex); // Protect last_meal_time
//         if(data->check)
//             return (NULL);
//         lock_forks(philo);  // Grab forks
//         pthread_mutex_unlock(&philo->shared_data->check_mutex);
//         eat(philo);  // This updates meals_eaten
//         sleep_func(philo);
//         think(philo);
//     }
//     return NULL;
// }

void    monitoring_closing_ths(t_philosopher   *philo, t_data *data, int i, int check)
{
    if (!check)
        printf("[%ld]: philooooo -> %d died\n", get_elapsed_time(data->start), philo[i].id);
    pthread_mutex_unlock(&philo[i].meal_mutex);
}


void *monitor(void *arg) // fix this after fising the eace condition problem in launch, eat atc.
{
    t_philosopher   *philo;
    t_data          *data;
    int i, meals;
    
    philo  = (t_philosopher*)arg;
    data = philo->shared_data;
    meals = 0;
    while (!data->check)
    {
        i = 0;
        while (i < data->p_n)
        {
            pthread_mutex_lock(&philo[i].meal_mutex); // Protect last_meal_time
            if (philo[i].meals_eaten == data->meals_to_eat)
                meals++;
            if(meals == data->meals_to_eat || ((get_current_time_ms() - philo[i].last_meal_time) >= data->t_d))
            {
                pthread_mutex_lock(&data->check_mutex); // Protect last_meal_time
                data->check = true;
                pthread_mutex_unlock(&data->check_mutex);
                if(meals == data->meals_to_eat)
                    monitoring_closing_ths(philo, data, i, 1);
                else 
                    monitoring_closing_ths(philo, data, i, 0);
                return (NULL);
            }
            pthread_mutex_unlock(&philo[i].meal_mutex);
            i++;
        }
        precise_sleep(1000);
    }
    return (NULL);
}

void    threads_production(pthread_t *philos, t_philosopher *philosophers, int i)
{
    while(i < philosophers->shared_data->p_n && !philosophers->shared_data->check)
    {
        pthread_create(&philos[i], NULL, routine, &philosophers[i]);
        i += 2;
    }

}

void launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data)
{
    int i = 0;
    pthread_t monitor_thread;

    // Start all philosopher threads first
    threads_production(philos, philo_struct, 0);
    if (philo_struct->shared_data->p_n >= 2)
    {
        precise_sleep(10);
        threads_production(philos, philo_struct, 1);
    }

    // ✅ After all philosophers have been launched, start monitor
    pthread_create(&monitor_thread, NULL, monitor, philo_struct);

    pthread_join(monitor_thread, NULL);

    // Wait for all philosopher threads to finish
    i = 0;
    while (i < data->p_n)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
}

// void launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data)
// {
//     int i = 0;
//     pthread_t monitor_thread;
    
//     pthread_create(&monitor_thread, NULL, monitor, philo_struct);
	
//     threads_production(philos, philo_struct, 0);
//     if (philo_struct->shared_data->p_n >= 2)
//     {
//         precise_sleep(10);
// 		threads_production(philos, philo_struct, 1);
//     }
//     pthread_join(monitor_thread, NULL);
//     i = 0;
//     while(i < data->p_n)
//     {
//         pthread_join(philos[i], NULL);
//         i++;
//     }
// }

