#include "philosophers.h"


// Get current time in milliseconds
long get_current_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// Get elapsed time since program start
long get_elapsed_time(long start_time)
{
    return (get_current_time_ms() - start_time);
}

// Sleep for specified milliseconds

void precise_sleep(int milliseconds)
{
    usleep(milliseconds * 1000); // usleep takes microseconds
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

int should_die(t_philosopher* philo) // check later something makes no sense in here 
{
    long current_time ;
    long time_since_last_meal ;

    current_time = get_current_time_ms();
    time_since_last_meal = current_time - philo->last_meal_time;
    if (time_since_last_meal > philo->shared_data->t_d)
        return (1);
    return (0);
}