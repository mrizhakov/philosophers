/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:43 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/23 19:05:32 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	print_out(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->n_philos_finished == philo->data->num_philo)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->death = 1;
		philo->dead = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (0);
	}
	if (philo->data->death != 1)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lu %d %s\n", (get_time(philo) - philo->start), philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (0);
	}
	philo->dead = 1;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sig;
	int		res;

	i = 0;
	sig = 1;
	res = 0;
	error_no_digit(str);
	if (str[0] == '-')
	{
		sig = -1;
		str++;
	}
	while (str[i])
	{
		res = res + (str[i] - '0');
		if (str[i + 1] != '\0')
			res = res * 10;
		i++;
	}
	return (res * sig);
}

uint64_t	ft_atoi_uint64t(char *str)
{
	int			i;
	uint64_t	sig;
	uint64_t	res;

	i = 0;
	sig = 1;
	res = 0;
	error_no_digit(str);
	if (str[0] == '-')
	{
		sig = -1;
		str++;
	}
	while (str[i])
	{
		res = res + (str[i] - '0');
		if (str[i + 1] != '\0')
			res = res * 10;
		i++;
	}
	return (res * sig);
}
