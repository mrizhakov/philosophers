/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:22:38 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/19 22:01:46 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_usleep(t_philo *philo, unsigned long long duration)
{
	unsigned long long	start_time;

	start_time = get_time(philo);
	while (get_time(philo) - start_time < duration)
		;
}

void	*ft_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	pthread_mutex_lock(&philo->data->death_time_mutex);
	philo->death_after_eating = philo->start + philo->t_die;
	pthread_mutex_unlock(&philo->data->death_time_mutex);
	print_out(philo, "is thinking");
	while (philo->dead == 0)
	{
		philo->hungry = 1;
		if (ft_eat(philo) == 1)
			break ;
		else
		{
			print_out(philo, "is sleeping");
			if (philo->dead != 1)
			{
				ft_usleep(philo, philo->t_sleep);
				print_out(philo, "is thinking");
			}
			else
				break ;
		}
	}
	return (NULL);
}

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
