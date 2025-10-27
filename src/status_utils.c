/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:58:38 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 12:01:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Lock the first and second fork mutexes and print to standard output
 * for both forks.
 */
void	philo_pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_first);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_second);
	print_status(philo, "has taken a fork");
}

/**
 * @brief Unlock the first and second fork mutexes.
 */
void	philo_return_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_first);
	pthread_mutex_unlock(philo->fork_second);
}

/**
 * @brief Update the philosophers `last_meal` and `meals_eaten` values.
 *
 * To prevent race conditions it will lock `mutex_eat` before writing.
 */
void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_eat);
	philo->last_meal = get_msec();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_eat);
}
