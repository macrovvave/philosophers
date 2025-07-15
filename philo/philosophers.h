/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macroooowave <macroooowave@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:31:23 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/07/15 19:21:29 by macroooowav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data
{
	int					meals;
	bool				check;
	bool				one;
	long long			p_n;
	long long			t_d;
	long long			t_s;
	long long			t_e;
	int					meals_to_eat;
	long long			tmp;
	long				start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		check_mutex;
	pthread_mutex_t		data_meal_counter_mutex;
	pthread_mutex_t		print;
}						t_data;

typedef struct s_philosopher
{
	int					id;
	int					l_fork;
	int					r_fork;
	long				last_meal_time;
	int					meals_eaten;
	t_data				*shared_data;
	pthread_mutex_t		meal_mutex;
}						t_philosopher;

void		ft_print(char *txt, long time, t_philosopher *philo, int n);
void		cleanup(t_data *data, t_philosopher *philos, pthread_t *threads);
long		get_current_time_ms(void);
long long	ft_atoi(char *str, long long *var);
void		launch(pthread_t *philos,
				t_philosopher *philo_struct, t_data *data);
void		sleep_func(t_philosopher *philo);
void		think(t_philosopher *philo);
void		eat(t_philosopher *philo);
void		lock_forks(t_philosopher *philo);
void		unlock_forks(t_philosopher *philo);
int			should_die(t_philosopher *philo);
int			ate_enough(t_philosopher *philo);
int			check_values(t_data *data);
void		ft_usleep(long long duration, t_philosopher *philo);
void		printing(int check, t_philosopher *philo);
long		el_time(long start_time);
t_data		*data(void);

#endif