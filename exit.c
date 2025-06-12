#include "philosophers.h"


void cleanup(t_data *data, t_philosopher *philos, pthread_t *threads)
{
	int i;

	i = 0;
    while (i < data->p_n)
		pthread_mutex_destroy(&data->forks[i++]);
	i = 0;
    while (i < data->p_n)
        pthread_mutex_destroy(&philos[i++].meal_mutex);
    if(data->forks)
        free(data->forks);
    if(philos)
        free(philos);
    if(threads)
        free(threads);
    if(data)
        free(data);
}