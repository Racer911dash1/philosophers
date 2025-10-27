/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:00:25 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 10:11:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initialize everything for the simulation including the values from
 * @brief @p `argc` and @p `argv`.
 *
 * @param[in,out]	table	The simulated table to initialize.
 * @param[in]		argc	Argument count from main.
 * @param[in]		argv	Argument vector from main.
 *
 * @return `false` should malloc or the mutex initialization fail,
 * @return `true` otherwise.
 */
bool	init(t_table *table, int argc, const char *argv[])
{
	init_table(table, argc, argv);
	if (malloc_threads(table) == false || init_mutex(table) == false \
|| init_philos(table) == false)
		return (false);
	return (true);
}
