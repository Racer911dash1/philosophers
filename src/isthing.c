/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isthing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:40:21 by dbakker           #+#    #+#             */
/*   Updated: 2025/09/29 10:13:06 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @return `true` if @p `c` is a whitespace character, `false` otherwise.
 */
bool	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/**
 * @return `true` if @p `c` is a decimal digit, `false` otherwise.
 */
bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
