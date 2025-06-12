#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>       // printf()
#include <stdlib.h>      // malloc(), free(), atoi()
#include <pthread.h>     // pthread functions and types
#include <sys/time.h>    // gettimeofday(), struct timeval
#include <unistd.h>      // usleep()

typedef struct s_data
{
	long long p_n;
	long long t_d;
	long long t_s;
	long long t_e;
	int meals;
	int number_of_meals;
	int start;
	pthread_mutex_t *forks;
} t_data;

typedef struct s_philosopher {
    int id;                    // Philosopher number (0, 1, 2, 3, 4)
    int left_fork_id;          // Which fork is on their left
    int right_fork_id;         // Which fork is on their right
    long last_meal_time;       // When they last started eating
    int meals_eaten;           // How many times they've eaten
    t_data *shared_data;       // Pointer to shared program data
} t_philosopher;

long get_current_time_ms();
long get_elapsed_time(long start_time);
long long ft_atoi(char *str);
void launch(pthread_t *philos, t_philosopher *philo_struct, t_data *data);
void precise_sleep(int milliseconds);
void sleep_func( t_philosopher* philo);
void think( t_philosopher* philo);
void eat( t_philosopher* philo);





#endif