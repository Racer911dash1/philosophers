/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:32:28 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 11:43:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Print to standard error with the custom message @p `str`.
 */
void	print_error(const char *str)
{
	const char	strerr[] = RED"=====Error=====\n"BRIGHT_CYAN;

	write(STDERR_FILENO, strerr, sizeof(strerr) - 1);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, DEFAULT, sizeof(DEFAULT) - 1);
}

/**
 * @brief Print to standard output with the action the philosopher is
 * @brief performing.
 *
 * It will print the time passed since the simulation, the id + 1 of the
 * philosopher and @p `status` should the simulation not have ended.
 *
 * To prevent race conditions, it will lock `mutex_print` and `mutex_dead` before
 * reading and executing.
 */
void	print_status(t_philo *philo, const char *status)
{
	time_t	time_passed;

	if (philo == NULL)
		return ;
	pthread_mutex_lock(&philo->table->mutex_print);
	time_passed = get_msec() - philo->table->time_start;
	pthread_mutex_lock(&philo->table->mutex_dead);
	if (philo->table->simulation_end == false)
		printf("%li %i %s\n", time_passed, philo->id + 1, status);
	pthread_mutex_unlock(&philo->table->mutex_dead);
	pthread_mutex_unlock(&philo->table->mutex_print);
}
