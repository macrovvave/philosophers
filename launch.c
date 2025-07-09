#include "philosophers.h"


void* routine(void* arg)
{
    t_philosopher   *philo = (t_philosopher*)arg;
    t_data          *data = philo->shared_data;

    while ((philo->meals_eaten < data->meals_to_eat || data->meals_to_eat == -1))
    {
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

        if (data->meals_to_eat != -1 && philo->meals_eaten >= data->meals_to_eat)
            break;
    }
    return NULL;
}


void *monitor(void *arg)
{
    t_philosopher   *philo;
    int i;
    
    philo  = (t_philosopher*)arg;
    while (!philo->shared_data->check)
    {
        i = 0;
        while (i++ < philo->shared_data->p_n)
        {
            if (philo->shared_data->meals == philo->shared_data->p_n
                || (get_current_time_ms() - philo->last_meal_time > philo->shared_data->t_d))
            {
                pthread_mutex_lock(&philo->shared_data->check_mutex); 
                philo->shared_data->check = true;
                if ((get_current_time_ms() - philo->last_meal_time > philo->shared_data->t_d))
                    printf("[%ld]: %d died\n",(get_current_time_ms() - philo->shared_data->start), philo->id);
                else
                    printf("[%ld]: all the philos ate thier meals\n", (get_current_time_ms() - philo->shared_data->start));
                pthread_mutex_unlock(&philo->shared_data->check_mutex);
                return (NULL);
            }
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

