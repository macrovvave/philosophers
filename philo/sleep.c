

#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	el_time(long start_time)
{
	return (get_current_time_ms() - start_time);
}

void	ft_usleep(long long duration, t_philosopher *philo)
{
	long long	end_time;

	end_time = get_current_time_ms() + duration;
	// pthread_mutex_lock(&philo->shared_data->sleep);// 8.0 lock
	while (get_current_time_ms() < end_time)
	{
		pthread_mutex_lock(&philo->shared_data->check_mutex); // 9.0 lock
		if(philo->shared_data->check)
		{
			pthread_mutex_unlock(&philo->shared_data->check_mutex);// 9.1 unlock
			return ;
		}
		pthread_mutex_unlock(&philo->shared_data->check_mutex); // 9.0 lock
		usleep(100);
	}
}

void	sleep_func(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->shared_data->check_mutex); // 7.0 lock
	if (!philo->shared_data->check)
	{
		pthread_mutex_unlock(&philo->shared_data->check_mutex); // 7.1 unlock
		printing(1, philo);
		ft_usleep(philo->shared_data->t_s, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->shared_data->check_mutex);// 7.2 unlock
}
