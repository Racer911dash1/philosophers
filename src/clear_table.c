/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:07:06 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 10:04:56 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Clean the entire table, including freeing allocated memory,
 * initialized mutexes and created threads.
 */
void	free_all(t_table *table)
{
	join_threads(table, table->philo_count);
	destroy_mutexes(table);
	free_heap(table);
}

/**
 * @brief Free all allocated memory for the philosophers and forks.
 */
void	free_heap(t_table *table)
{
	if (table->philos != NULL)
		free(table->philos);
	if (table->forks != NULL)
		free(table->forks);
}

/**
 * @brief Join all threads at simulation end, or after an error at creation.
 *
 * Should there be an error at creation, will @p `thread_count` be assigned a
 * value for the amount of successful threads created.
 *
 * @param[out]	table			Pointer to the table.
 * @param[in]	thread_count	Amount of threads to join.
 *
 * @return `false` if the threads could not be joined, `true` otherwise.
 */
bool	join_threads(t_table *table, int32_t thread_count)
{
	int32_t	i;

	i = 0;
	while (i < thread_count)
		if (pthread_join(table->philos[i++].philo, NULL) != 0)
			return (print_error("Failed joining threads\n"), false);
	return (true);
}

/**
 * @brief Destroy all created mutexes after the simulation ended.
 */
void	destroy_mutexes(t_table *table)
{
	int32_t	i;

	i = 0;
	pthread_mutex_destroy(&table->mutex_barrier);
	pthread_mutex_destroy(&table->mutex_dead);
	pthread_mutex_destroy(&table->mutex_print);
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i++].mutex_eat);
	}
}
