/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:16:01 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 12:23:29 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief The Philosophers eat action.
 */
void	philo_eat(t_philo *philo)
{
	philo_pickup_forks(philo);
	print_status(philo, "is eating");
	update_meal_info(philo);
	ft_usleep(philo, philo->table->time_to_eat);
	philo_return_forks(philo);
}

/**
 * @brief The Philosophers sleep action.
 */
void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo, philo->table->time_to_sleep);
}

/**
 * @brief The Philosophers think action.
 *
 * For odd philosophers, they will think for twice the `time_to_eat`
 * minus the `time_to_think` to prevent a monopoply on the forks.
 */
void	philo_think(t_philo *philo)
{
	time_t	t_think;

	print_status(philo, "is thinking");
	if (philo->table->philo_count % 2 == 1)
	{
		t_think = (philo->table->time_to_eat * 2) - philo->table->time_to_sleep;
		ft_usleep(philo, t_think);
	}
}
