/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:44:38 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/27 11:02:20 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char *argv[])
{
	t_table	table;

	if (check_input(argc, argv) == false)
		return (EXIT_FAILURE);
	if (init(&table, argc, argv) == false)
		return (free_heap(&table), EXIT_FAILURE);
	if (launch_routine(&table) == false)
		return (free_heap(&table), EXIT_FAILURE);
	return (free_all(&table), EXIT_SUCCESS);
}
