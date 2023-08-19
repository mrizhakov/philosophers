/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:35 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/19 21:12:10 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_die_verify_ext(t_philo *philo)
{
	usleep(philo->t_eat);
	pthread_mutex_lock(&philo->data->dead_mutex);
	philo->data->death = 1;
	philo->dead = 1;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->dead_mutex);
}

int	ft_die_verify(t_philo *philo, uint64_t start)
{
	uint64_t	death_time;
	uint64_t	current_time;

	pthread_mutex_lock(&philo->data->death_time_mutex);
	death_time = philo->death_after_eating;
	pthread_mutex_unlock(&philo->data->death_time_mutex);
	current_time = get_time(philo);
	if (philo->data->n_philos_finished == philo->data->num_philo)
	{
		ft_die_verify_ext(philo);
		return (2);
	}
	else if ((current_time - start) > death_time || philo->alone == 1)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->death = 1;
		philo->dead = 1;
		pthread_mutex_lock(&philo->data->print_mutex);
		if ((current_time - start) > death_time || philo->alone == 1)
			printf("%lu %d %s\n", current_time - start, philo->id, "died");
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	return (0);
}

void	ft_monitor(t_data *data)
{
	int	i;

	i = 0;
	usleep(data->time_to_die * (1000 - 1));
	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (ft_die_verify(data->philo[i], data->start) == 0)
				i++;
			else
				return ;
		}
	}
}
