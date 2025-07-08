#include "philosophers.h"

void lock_forks(t_philosopher* philo )
{
    pthread_mutex_lock(&philo->shared_data->forks[philo->left_fork_id]);
    pthread_mutex_lock(&philo->shared_data->forks[philo->right_fork_id]);

    // After both forks are locked, check if simulation has ended
    pthread_mutex_lock(&philo->shared_data->check_mutex);
    if (!philo->shared_data->check)
    {
        pthread_mutex_lock(&philo->shared_data->printing_mutex);
    	printf("[%ld]: %d has taken two forks\n", get_elapsed_time(philo->shared_data->start), philo->id);
        pthread_mutex_unlock(&philo->shared_data->printing_mutex);
    }
    else
    {
        pthread_mutex_unlock(&philo->shared_data->check_mutex);
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

        eat(philo);
        sleep_func(philo);
        think(philo);

        // If you want to exit after meals, check here
        if (data->meals_to_eat != -1 && philo->meals_eaten >= data->meals_to_eat)
            break;
    }
    return NULL;
}


// void    monitoring_closing_ths(t_philosopher *philo, t_data *data, int i, int check)
// {
//     if (!check)
//     {
//     	pthread_mutex_lock(&data->printing_mutex);
//         printing(philo, 4);
//         pthread_mutex_unlock(&data->printing_mutex);
//     }
//     else
//     {
//         pthread_mutex_lock(&data->printing_mutex);
//         printing(philo, 0);
//         pthread_mutex_unlock(&data->printing_mutex);
//     }
//     pthread_mutex_unlock(&philo[i].meal_mutex);
// }

// pthread_mutex_lock(&philo[i].meal_mutex); // Protect last_meal_time
//             printf("%d philo[i].meals_eaten == %d\n", philo[i].id, philo[i].meals_eaten);
//         	if (philo[i].meals_eaten == data->meals_to_eat)
//                 meals++;
//             pthread_mutex_unlock(&philo[i].meal_mutex);

void *monitor(void *arg) // fix this after fising the eace condition problem in launch, eat atc.
{
    t_philosopher   *philo;
    t_data          *data;
    int i;
    
    philo  = (t_philosopher*)arg;
    data = philo->shared_data;
    while (!data->check)
    {
        i = 0;
        while (i < data->p_n)
        {
            if (data->meals == data->p_n || should_die(&philo[i]))
            { 
                pthread_mutex_lock(&data->check_mutex); 
                data->check = true;
                pthread_mutex_unlock(&data->check_mutex);
                if (data->meals == data->p_n)
                {
	                // pthread_mutex_lock(&philo->shared_data->printing_mutex);
                    printf("[%ld]: all the philos ate thier meals \n", get_elapsed_time(philo->shared_data->start));
	                // pthread_mutex_unlock(&philo->shared_data->printing_mutex);
                }
                else
                {
	                // pthread_mutex_lock(&philo->shared_data->printing_mutex);
                    printf("[%ld]: philooOooOo -> %d died\n", get_elapsed_time(philo->shared_data->start), philo->id);
                	// pthread_mutex_unlock(&philo->shared_data->printing_mutex);					
				}
                return (NULL);
            }
            i++;
        }
        precise_sleep(500);
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

    data->start = get_current_time_ms();
    threads_production(philos, philo_struct, 0);
    if (philo_struct->shared_data->p_n >= 2)
    {
        precise_sleep(100);
        threads_production(philos, philo_struct, 1);
    }
    pthread_create(&monitor_thread, NULL, monitor, philo_struct);

    pthread_join(monitor_thread, NULL);

    i = 0;
    while (i < data->p_n)
        pthread_join(philos[i++], NULL);
}

