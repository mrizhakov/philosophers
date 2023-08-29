/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:48 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/23 18:30:51 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

uint64_t	get_start_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	get_time(t_philo *philo)
{
	struct timeval	tv;
	uint64_t		time;

	pthread_mutex_lock(&philo->data->time_mutex);
	time = 0;
	if (gettimeofday(&tv, NULL))
		return (0);
	time = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&philo->data->time_mutex);
	return (time);
}
