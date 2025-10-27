/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:25:53 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 12:30:39 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief End the simulation be setting the member variable `simulation_end`
 * @brief from @p `table` to `true`.
 *
 * To prevent race conditions it will lock `mutex_dead` before writing.
 */
static void	end_simulation(t_table *table)
{
	pthread_mutex_lock(&table->mutex_dead);
	table->simulation_end = true;
	pthread_mutex_unlock(&table->mutex_dead);
}

/**
 * @brief Check whether the philosopher starved to death.
 *
 * It will check that by taking the current time and subtracting it by the time
 * of its last meal. It will print to the standard output should the philosopher
 * die.
 *
 * @param[in,out]	table	Pointer to the simulated table.
 * @param[in]		data	Data from the current philosopher.
 *
 * @return `true` if the philosopher died, `false` otherwise.
 */
static bool	check_philo_death(t_table *table, t_eat_data data)
{
	if (get_msec() - data.last_meal > table->time_to_die)
	{
		end_simulation(table);
		pthread_mutex_lock(&table->mutex_print);
		printf("%li %i %s\n", get_msec() - table->time_start, data.i + 1, \
"died");
		pthread_mutex_unlock(&table->mutex_print);
		return (true);
	}
	return (false);
}

/**
 * @brief Copy the data from the philosopher to prevent stalling.
 *
 * To prevent race conditions it will lock `mutex_eat` before copying.
 *
 * @param[in,out]	table	Pointer to the simulated table to lock the mutex.
 * @param[out]		data	Values to copy to.
 */
static void	obtain_philo_data(t_table *table, t_eat_data *data)
{
	pthread_mutex_lock(&table->philos[data->i].mutex_eat);
	data->last_meal = table->philos[data->i].last_meal;
	data->meals_eaten = table->philos[data->i].meals_eaten;
	pthread_mutex_unlock(&table->philos[data->i].mutex_eat);
}

/**
 * @brief Check if any philosopher died or all philosophers have eaten the
 * @brief required amount.
 *
 * @return `true` either condition is met, `false` otherwise.
 */
static bool	check_philo_status(t_table *table)
{
	t_eat_data	data;

	memset(&data, 0, sizeof(t_eat_data));
	while (data.i < table->philo_count)
	{
		obtain_philo_data(table, &data);
		if (check_philo_death(table, data) == true)
			return (true);
		if (data.meals_eaten >= table->amount_to_eat)
			data.meals_finished++;
		data.i++;
	}
	if (data.meals_finished == table->philo_count && table->amount_to_eat != -1)
		return (end_simulation(table), true);
	return (false);
}

/**
 * @brief Will periodically check if the simulation ended. Either due to a
 * @brief philosopher starving to death, or if every philosopher has eaten
 * @brief enough.
 *
 * The check will be run every 0.5 milliseconds.
 */
void	monitor(t_table *table)
{
	while (check_philo_status(table) == false)
		usleep(500);
}
