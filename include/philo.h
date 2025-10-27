/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:44:34 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 10:26:34 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define _DEFAULT_SOURCE

# include <string.h> // memset()
# include <stdlib.h> // malloc(), free()
# include <stdio.h> // printf()
# include <unistd.h> // write(), usleep()
# include <sys/time.h> // gettimeofday()
# include <pthread.h> // Functions starting with pthread_

# include <stdbool.h> // true or false
# include <stdint.h> // int32_t

# define RED "\e[31m"
# define GREEN "\e[32m"
# define MAGENTA "\e[35m"
# define DEFAULT "\e[39;49m"
# define BRIGHT_YELLOW "\e[93m"
# define BRIGHT_BLUE "\e[94m"
# define BRIGHT_CYAN "\e[96m"

# define ERROR_ARGC "Usage: ./philo \"Number of Philosophers\" \"Time to die\"\
 \"Time to eat\" \"Time to sleep\"\
 [\"Number of times each Philosopher must eat\"]\n"
# define ERROR_ARGV "Only numbers above 0 are allowed\n"
# define ERROR_MALLOC_PHILO "Failed allocating memory for table->philos\n"
# define ERROR_MALLOC_FORKS "Failed allocating memory for table->forks\n"
# define ERROR_MUTEX_BARRIER "Failed initializing table->mutex_barrier\n"
# define ERROR_MUTEX_DIED "Failed initializing table->mutex_dead\n"
# define ERROR_MUTEX_EAT "Failed initializing table->mutex_eat\n"
# define ERROR_MUTEX_PRINT "Failed initializing table->mutex_print\n"
# define ERROR_MUTEX_FORKS "Failed initializing table->forks\n"

typedef struct s_table	t_table;

enum e_input
{
	PHILO_COUNT = 1,
	TIME_TO_DIE = 2,
	TIME_TO_EAT = 3,
	TIME_TO_SLEEP = 4,
	AMOUNT_TO_EAT = 5
};

/**
 * @struct s_eat_data
 *
 * Its purpose is to copy the data from the philosopher without stalling it.
 */
typedef struct s_eat_data
{
	/** Index of the philosopher. */
	int32_t	i;
	/** Number of meals eaten for each philosopher. */
	int32_t	meals_eaten;
	/** How many philosophers finished eating their meal. */
	int32_t	meals_finished;
	/** Time since the philosopher has last eaten. */
	time_t	last_meal;
}	t_eat_data;

/**
 * @struct s_philo
 */
typedef struct s_philo
{
	/** Number of meals eaten. */
	int32_t			meals_eaten;
	/** A unique identifier between 0 and N. */
	int32_t			id;
	/** The created thread. */
	pthread_t		philo;
	/** Prevention of a data race with the main thread. */
	pthread_mutex_t	mutex_eat;
	/** Depending on whether the `id` is even or odd, will its first fork be
	 * left or right. */
	pthread_mutex_t	*fork_first;
	/** The second fork to be picked up after the first. */
	pthread_mutex_t	*fork_second;
	/** The time of the last meal in ms. */
	time_t			last_meal;
	/** Pointer to the table for additional data. */
	t_table			*table;
}	t_philo;

/**
 * @struct s_table
 */
typedef struct s_table
{
	/** Condition whether the simulation ended due to starvation or meal amount
	 * met between all philosophers. */
	bool			simulation_end;
	/** Amount of philosophers in the simulation.
	 * An equal amount of threads will be made. */
	int32_t			philo_count;
	/** Maximum time allowed to not eat in ms. */
	int32_t			time_to_die;
	/** Time in ms. */
	int32_t			time_to_eat;
	/** Time in ms after eating. */
	int32_t			time_to_sleep;
	/** How many times every philosopher should eat.
	 * Set to -1 if not specified. */
	int32_t			amount_to_eat;
	/** Global start timer in ms. */
	time_t			time_start;
	/** Global mutex to synchronize all philosophers. */
	pthread_mutex_t	mutex_barrier;
	/** Global mutex to check `simulation end`. */
	pthread_mutex_t	mutex_dead;
	/** Global mutex for printing to the standard output. */
	pthread_mutex_t	mutex_print;
	/** Amount of forks in the simulation.
	 * The ratio between `forks` and `philo_count` is equal.*/
	pthread_mutex_t	*forks;
	/** Pointer to `philo_count` philosophers. */
	t_philo			*philos;
}	t_table;

// checker.c

bool	check_input(int argc, const char *argv[]);
// clear_table.c

void	free_all(t_table *table);
void	free_heap(t_table *table);
bool	join_threads(t_table *table, int32_t thread_count);
void	destroy_mutexes(t_table *table);
// init_utils.c

void	init_table(t_table *table, int argc, const char *argv[]);
bool	malloc_threads(t_table *table);
bool	init_mutex(t_table *table);
bool	init_philos(t_table *table);
// init.c

bool	init(t_table *table, int argc, const char *argv[]);
// issthing.c

bool	ft_isspace(int c);
bool	ft_isdigit(int c);
// monitor.c

void	monitor(t_table *table);
// print.c

void	print_error(const char *str);
void	print_status(t_philo *philo, const char *status);
// routine.c

bool	launch_routine(t_table *table);
// status_utils.c

void	philo_pickup_forks(t_philo *philo);
void	philo_return_forks(t_philo *philo);
void	update_meal_info(t_philo *philo);
// status.c

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
// utils.c

size_t	ft_strlen(const char *str);
int32_t	ft_atoi(const char *str);
time_t	get_msec(void);
void	ft_usleep(t_philo *philo, int32_t wait_time);
bool	simulation_ended(t_table *table);

void	print_args(t_table table);
void	print_philo(t_table table, bool loop);
#endif