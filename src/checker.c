/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:21:52 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 10:07:23 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @return false if @p `argc` is not 5 or 6, true otherwise.
 */
static bool	check_argc(int argc)
{
	if (argc < 5 || argc > 6)
		return (print_error(ERROR_ARGC), false);
	return (true);
}

/**
 * @return false if any string of @p `argv` is 0 or less, true otherwise.
 */
static bool	check_argv(int argc, const char *argv[])
{
	int32_t	i;

	i = 1;
	while (i < argc)
		if (ft_atoi(argv[i++]) <= 0)
			return (print_error(ERROR_ARGV), false);
	return (true);
}

/**
 * @brief Check if all the program arguments are valid.
 *
 * @p `argc` should be between 5 and 6 arguments and @p `argv` should only
 * contain positive 32 bit integers.
 *
 * @param[in] argc Amount of arguments.
 * @param[in] argv Array of strings.
 *
 * @return `false` if either arg has incorrect values, `true` otherwise.
 */
bool	check_input(int argc, const char *argv[])
{
	if (check_argc(argc) == false || check_argv(argc, argv) == false)
		return (false);
	return (true);
}
