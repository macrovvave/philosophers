#include "philosophers.h"


// Get current time in milliseconds
long get_current_time_ms()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000L) + (ts.tv_nsec / 1000000L);
}

// Get elapsed time since program start
long get_elapsed_time(long start_time)
{
    return (get_current_time_ms() - start_time);
}

// Sleep for specified milliseconds

void precise_sleep(int milliseconds)
{
    struct timespec req;

    req.tv_sec = milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000L;

    nanosleep(&req, NULL);
}

long long ft_atoi(char *str)
{
	int i;
	long long result;

	i = 0;
	result = 0;
	while(str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

int	should_die(t_philosopher *philo)
{
	long	time_diff;

	pthread_mutex_lock(&philo->meal_mutex);
	time_diff = get_current_time_ms() - philo->last_meal_time;
	if (time_diff >= philo->shared_data->t_d)
	{
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = 1;
		philo->shared_data->death_time = time_diff;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	ate_enough(t_philosopher *philo)
{
	int	i;
	int	all_ate;

	if (philo->shared_data->meals_to_eat <= 0)
		return (0);
	i = 0;
	all_ate = 1;
	while (i < philo->shared_data->p_n)
	{
		if (philo[i].meals_eaten < philo->shared_data->meals_to_eat)
			all_ate = 0;
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&philo->shared_data->check_mutex);
		philo->shared_data->check = 1;
		philo->shared_data->done_time = get_current_time_ms()
			- philo->shared_data->start;
		pthread_mutex_unlock(&philo->shared_data->check_mutex);
		return (1);
	}
	return (0);
}


// int ate_enough(t_philosopher   *philo)
// {
//     if (philo->shared_data->meals == philo->shared_data->p_n)
//     {
//         philo->shared_data->done_time = get_current_time_ms() - philo->shared_data->start;
//         pthread_mutex_lock(&philo->shared_data->check_mutex); 
//         philo->shared_data->check = true;
//         pthread_mutex_unlock(&philo->shared_data->check_mutex);
//         return (1);
//     }
//     return (0);
// }

// int should_die(t_philosopher   *philo)
// {
//     philo->shared_data->death_time = get_current_time_ms() - philo->shared_data->start;
//     if (philo->shared_data->death_time >= philo->shared_data->t_d)
//     {
//         pthread_mutex_lock(&philo->shared_data->check_mutex); 
//         philo->shared_data->check = true;
//         pthread_mutex_unlock(&philo->shared_data->check_mutex);
//         return (1);
//     }
//     return (0);
// }