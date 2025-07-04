#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>       // printf()
#include <stdlib.h>      // malloc(), free(), atoi()
#include <pthread.h>     // pthread functions and types
#include <sys/time.h>    // gettimeofday(), struct timeval
#include <unistd.h>      // usleep()
#include <stdbool.h>

typedef struct s_data
{
	bool check;
	long long p_n;
	long long t_d;
	long long t_s;
	long long t_e;
	int meals_to_eat;
	int number_of_meals;
	long start;
	pthread_mutex_t *forks;
	pthread_mutex_t check_mutex;       // Pointer to shared program data
} t_data;

typedef struct s_philosopher {
    int id;                    // Philosopher number (0, 1, 2, 3, 4)
    int left_fork_id;          // Which fork is on their left
    int right_fork_id;         // Which fork is on their right
    long last_meal_time;       // When they last started eating
    int meals_eaten;
    t_data *shared_data;
	pthread_mutex_t meal_mutex;       // Pointer to shared program data
} t_philosopher;

void cleanup(t_data *data, t_philosopher *philos, pthread_t *threads);
long get_current_time_ms();
long get_elapsed_time(long start_time);
long long ft_atoi(char *str);
void launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data);
void precise_sleep(int milliseconds);
void sleep_func( t_philosopher* philo);
void think( t_philosopher* philo);
void eat( t_philosopher* philo);
void unlock_forks(t_philosopher* philo );
t_data *data();


#endif