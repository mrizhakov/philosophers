/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:35 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/24 18:34:15 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_die_verify_update_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	philo->data->death = 1;
	philo->dead = 1;
	pthread_mutex_unlock(&philo->data->dead_mutex);
}

uint64_t	ft_update_death_time(t_philo *philo)
{
	uint64_t	death_time;

	pthread_mutex_lock(&philo->data->death_time_mutex);
	death_time = philo->death_after_eating;
	pthread_mutex_unlock(&philo->data->death_time_mutex);
	return (death_time);
}

int	ft_die_verify(t_philo *philo, uint64_t start)
{
	uint64_t	death_time;
	uint64_t	current_time;

	death_time = ft_update_death_time(philo);
	current_time = get_time(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->n_philos_finished == philo->data->num_philo)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		usleep(philo->t_eat);
		ft_die_verify_update_flag(philo);
		return (2);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if ((current_time - start) > death_time || philo->alone == 1)
	{
		ft_die_verify_update_flag(philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		if ((current_time - start) > death_time || philo->alone == 1)
			printf("%lu %d %s\n", current_time - start, philo->id, "died");
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

// int	ft_die_verify(t_philo *philo, uint64_t start)
// {
// 	uint64_t	death_time;
// 	uint64_t	current_time;

// 	pthread_mutex_lock(&philo->data->death_time_mutex);
// 	death_time = philo->death_after_eating;
// 	current_time = get_time(philo);
// 	pthread_mutex_unlock(&philo->data->death_time_mutex);
// 	pthread_mutex_lock(&philo->data->meal_mutex);
// 	if (philo->data->n_philos_finished == philo->data->num_philo)
// 	{
// 		pthread_mutex_unlock(&philo->data->meal_mutex);
// 		usleep(philo->t_eat);
// 		ft_die_verify_update_flag(philo);
// 		return (2);
// 	}
// 	pthread_mutex_unlock(&philo->data->meal_mutex);
// 	if ((current_time - start) > death_time || philo->alone == 1)
// 	{
// 		ft_die_verify_update_flag(philo);
// 		pthread_mutex_lock(&philo->data->print_mutex);
// 		if ((current_time - start) > death_time || philo->alone == 1)
// 			printf("%lu %d %s\n", current_time - start, philo->id, "died");
// 		pthread_mutex_unlock(&philo->data->print_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

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
