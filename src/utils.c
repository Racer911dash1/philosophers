/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:49:40 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 12:10:53 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Calculate the length of @p `str` excluding the terminating null byte.
 *
 * @param[in]	str	The string to get the length of.
 *
 * @return The length of @p `str`.
 */
size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

/**
 * @brief Convert @p `str` to a 32-bit integer.
 *
 * @param[in]	str	The String to convert.
 *
 * @return The converted value, or 0 on error.
 *
 * @note ft_atoi does not detect valid input or overflow.
 */
int32_t	ft_atoi(const char *str)
{
	int32_t	index;
	int32_t	number;
	int32_t	sign;

	index = 0;
	number = 0;
	sign = 1;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
		if (str[index++] == '-')
			sign = -sign;
	while (ft_isdigit(str[index]))
		number = number * 10 + (str[index++] - '0');
	return (number * sign);
}

/**
 * @brief Return the time in ms since the UNIX epoch.
 */
time_t	get_msec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

/**
 * @brief Sleep atleast @p `wait_time` ms in short bursts to periodically check
 * if the simulation ended.
 *
 * To prevent race conditions it will lock `mutex_dead` before reading.
 *
 * @param[in]	philo		Pointer to the philosopher.
 * @param[in]	wait_time	Time in ms for the philosopher to sleep.
 */
void	ft_usleep(t_philo *philo, int32_t wait_time)
{
	time_t	usleep_time;

	usleep_time = get_msec() + wait_time;
	while (get_msec() < usleep_time)
	{
		if (simulation_ended(philo->table) == true)
			break ;
		usleep(100);
	}
}

/**
 * @brief Check if the member variable simulation_end of @p `table` is true.
 *
 * To prevent race conditions it will lock `mutex_dead` before reading.
 *
 * @return `true` if simulation ended, `false` otherwise.
 */
bool	simulation_ended(t_table *table)
{
	pthread_mutex_lock(&table->mutex_dead);
	if (table->simulation_end == true)
		return (pthread_mutex_unlock(&table->mutex_dead), true);
	pthread_mutex_unlock(&table->mutex_dead);
	return (false);
}
