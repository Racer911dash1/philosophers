/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:18:34 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 10:11:51 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initialize the simulated table with values
 * @brief from @p `argc` and @p `argv`.
 *
 * Sets all simulation parameters in the @p `table` struct, including the
 * command line arguments. Also initializes all other member arguments to 0.
 *
 * @param[in,out]	table	Pointer to the simulated table to initialize.
 * @param[in]		argc	Argument count from main.
 * @param[in]		argv	Argument vector from main.
 *
 * @note If the optional meal argument is not provided,
 * @note `amount_to_eat` is set to -1.
 */
void	init_table(t_table *table, int argc, const char *argv[])
{
	memset(table, 0, sizeof(t_table));
	table->philo_count = ft_atoi(argv[PHILO_COUNT]);
	table->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	table->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	table->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	table->amount_to_eat = -1;
	if (argc == 6)
		table->amount_to_eat = ft_atoi(argv[AMOUNT_TO_EAT]);
}

/**
 * @brief Allocate memory for the philosophers and forks for the simulated
 * @brief table.
 *
 * @param[in,out] table Pointer to the simulated table.
 *
 * @return `false` if memory allocated failed for either pointer,
 * @return `true` otherwise.
 */
bool	malloc_threads(t_table *table)
{
	table->philos = malloc(table->philo_count * sizeof(t_philo));
	if (table->philos == NULL)
		return (print_error(ERROR_MALLOC_PHILO), false);
	table->forks = malloc(table->philo_count * sizeof(pthread_mutex_t));
	if (table->forks == NULL)
		return (print_error(ERROR_MALLOC_FORKS), false);
	return (true);
}

/**
 * @brief Initialize the mutexes for the simulated table.
 *
 * @param[in,out] table Pointer to the simulated table to initialize.
 *
 * @return `false` if the initialization of any mutex did not return 0,
 * @return `true` otherwise.
 */
bool	init_mutex(t_table *table)
{
	int32_t	i;

	i = 0;
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		return (print_error(ERROR_MUTEX_PRINT), false);
	if (pthread_mutex_init(&table->mutex_dead, NULL) != 0)
		return (print_error(ERROR_MUTEX_DIED), false);
	if (pthread_mutex_init(&table->mutex_barrier, NULL) != 0)
		return (print_error(ERROR_MUTEX_BARRIER), false);
	while (i < table->philo_count)
		if (pthread_mutex_init(&table->forks[i++], NULL) != 0)
			return (print_error(ERROR_MUTEX_FORKS), false);
	return (true);
}

/**
 * @brief Assign the order at which the forks should be picked up for each
 * @brief pilosopher.
 *
 * For every even philosopher will the forks be picked up in a left/right order.
 * For every odd philsopher will the forks be picked up in a right/left order.
 *
 * @param[in,out]	table		Pointer to the simulated table.
 * @param[in]		philo_id	The id for each philosopher.
 */
static void	assign_forks(t_table *table, int32_t philo_id)
{
	if (philo_id % 2 == 0)
	{
		table->philos[philo_id].fork_first = &table->forks[philo_id];
		table->philos[philo_id].fork_second = &table->forks[(philo_id + 1) % \
table->philo_count];
	}
	else
	{
		table->philos[philo_id].fork_first = &table->forks[(philo_id + 1) % \
table->philo_count];
		table->philos[philo_id].fork_second = &table->forks[philo_id];
	}
}

/**
 * @brief Initialize each philosopher with starting values.
 *
 * Each philosopher points back to the simulated table for its command line
 * arguments and other member variables, sets their id, assigns forks,
 * initializes the eat mutex for each philosopher and sets all other member
 * variables to 0.
 *
 * @param[in,out] table Pointer to the simulated table.
 *
 * @return `false` if the initialization of the mutex failed, `true` otherwise.
 */
bool	init_philos(t_table *table)
{
	int32_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		memset(&table->philos[i], 0, sizeof(t_philo));
		if (pthread_mutex_init(&table->philos[i].mutex_eat, NULL) != 0)
			return (print_error(ERROR_MUTEX_EAT), false);
		table->philos[i].id = i;
		assign_forks(table, i);
		table->philos[i++].table = table;
	}
	return (true);
}
