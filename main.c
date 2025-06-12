#include "philosophers.h"

t_data *parse_args(int argc, char **argv)
{
    t_data *data;
 
	data = malloc(sizeof(t_data));
	if(!data)
		return (NULL);    
    if(!(data->t_s = atoi(argv[4])) || !(data->t_e = atoi(argv[3])) 
		|| !(data->t_d = atoi(argv[2])) || !(data->p_n = atoi(argv[1])))
	{
		free(data);
		return (NULL);
	}
	if((argc == 6))
	{
		if(!(data->meals = atoi(argv[5])))
		{
			free(data);
			return (NULL);
		}
	}
	else
		data->meals = -1;
    data->start = get_current_time_ms();
    return data;
}


void inis(t_data *data, t_philosopher *philo)
{
	int i;

	i = 0;
	while( i < data->p_n) {
        philo[i].id = i;
        philo[i].left_fork_id = i;
        philo[i].right_fork_id = (i + 1) % data->p_n;
        philo[i].last_meal_time = get_current_time();
        philo[i].meals_eaten = 0;
		i++;
    }
	philo->shared_data = data;
}


int main(int ac, char **av)
{
	t_data *data;
	pthread_t *philosophers;           // Thread array
	t_philosopher *philo_structs;     // Philosopher data array

	if((ac != 5 && ac != 6) || !(data = pars(ac, av + 1)))
		return (0);
	else
	{
		data->start = get_current_time_ms();
		philosophers = malloc(sizeof(pthread_t) * data->p_n);
		data->forks = malloc(sizeof(pthread_mutex_t) * data->p_n);
		philo_structs = malloc(sizeof(t_philosopher) * data->p_n);
		if(!philosophers || !data->forks || !philo_structs)
		{
			free(data);
			return (0);
		}
	}
	inis(data, philo_structs);
	launch(philosophers, philo_structs, data);
}