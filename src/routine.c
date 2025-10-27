/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:26:48 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 11:58:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Edgecase in the event only a single philosopher is in the simulation.
 *
 * Because there is only one fork it will not be able to pick up the second
 * fork.
 */
static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_first);
	print_status(philo, "has taken a fork");
	ft_usleep(philo, philo->table->time_to_die);
	pthread_mutex_unlock(philo->fork_first);
	return (NULL);
}

/**
 * @brief The philosophers will undergo a routine here, in which they will
 * eat, sleep and think.
 *
 * Before starting they will all be synchronized to prevent any latecomers
 * and undergo a final check to see if all philosophers have been made.
 * Even philosophers will have a little delay before starting to ensure
 * an orderly simulation.
 *
 * @return `NULL` on simulation end.
 */
static void	*routine_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(&philo->table->mutex_barrier);
	if (simulation_ended(philo->table) == true)
		return (pthread_mutex_unlock(&philo->table->mutex_barrier), NULL);
	pthread_mutex_unlock(&philo->table->mutex_barrier);
	if (philo->table->philo_count == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 500);
	while (true != false)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (simulation_ended(philo->table) == true)
			break ;
	}
	return (NULL);
}

/**
 * @brief Start the simulation by creating the philosophers.
 *
 * `time_start` will be set to POSIX time in ms to define the starting point
 * an `mutex_barrier` will be locked to synchronize all philosophers.
 *
 * @return `false` if thread creation failed, `true` otherwise.
 */
bool	launch_routine(t_table *table)
{
	int32_t	i;

	i = 0;
	table->time_start = get_msec();
	pthread_mutex_lock(&table->mutex_barrier);
	while (i < table->philo_count)
	{
		table->philos[i].last_meal = table->time_start;
		if (pthread_create(&table->philos[i].philo, NULL, \
routine_philo, table->philos + i) != 0)
		{
			table->simulation_end = true;
			pthread_mutex_unlock(&table->mutex_barrier);
			join_threads(table, i);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&table->mutex_barrier);
	monitor(table);
	return (true);
}
