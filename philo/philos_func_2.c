/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:22:38 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/24 18:24:49 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	odd_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork_right->mutex) == 0)
	{
		print_out(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_left->mutex);
		print_out(philo, "has taken a fork");
		print_out(philo, "is eating");
		philo->current = get_time(philo) - philo->start;
		pthread_mutex_lock(&philo->data->death_time_mutex);
		philo->death_after_eating = philo->current + philo->t_die;
		pthread_mutex_unlock(&philo->data->death_time_mutex);
		philo->meals++;
		if (philo->meals == philo->meal_target)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			philo->data->n_philos_finished++;
			pthread_mutex_unlock(&philo->data->meal_mutex);
		}
		ft_usleep(philo, philo->t_eat);
		philo->hungry = 0;
		pthread_mutex_unlock(&philo->fork_right->mutex);
		pthread_mutex_unlock(&philo->fork_left->mutex);
	}
}

void	even_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork_left->mutex) == 0)
	{
		print_out(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_right->mutex);
		print_out(philo, "has taken a fork");
		print_out(philo, "is eating");
		philo->current = get_time(philo) - philo->start;
		pthread_mutex_lock(&philo->data->death_time_mutex);
		philo->death_after_eating = philo->current + philo->t_die;
		pthread_mutex_unlock(&philo->data->death_time_mutex);
		philo->meals++;
		if (philo->meals == philo->meal_target)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			philo->data->n_philos_finished++;
			pthread_mutex_unlock(&philo->data->meal_mutex);
		}
		ft_usleep(philo, philo->t_eat);
		philo->hungry = 0;
		pthread_mutex_unlock(&philo->fork_left->mutex);
		pthread_mutex_unlock(&philo->fork_right->mutex);
	}
}

int	ft_eat(t_philo *philo)
{
	philo->current = get_time(philo) - philo->start;
	if (philo->alone == 1)
	{
		print_out(philo, "has taken a fork");
		usleep(philo->t_die * 1000); 
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	else if (philo->id % 2 == 0)
		even_eat(philo);
	else if (philo->id % 2 == 1)
		odd_eat(philo);
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}
