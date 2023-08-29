/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:22:38 by kmooney           #+#    #+#             */
/*   Updated: 2023/08/24 18:24:41 by mrizakov         ###   ########.fr       */
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

int	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->dead != 0)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}

void	ft_check_death_2(t_philo *philo)
{
	if (philo->dead != 1)
	{
		ft_usleep(philo, philo->t_sleep);
		print_out(philo, "is thinking");
	}
}

void	ft_update_death_after_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_time_mutex);
	philo->death_after_eating = philo->start + philo->t_die;
	pthread_mutex_unlock(&philo->data->death_time_mutex);
}

void	*ft_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	ft_update_death_after_eating(philo);
	print_out(philo, "is thinking");
	while (1)
	{
		if (ft_check_death(philo) == 1)
			return (NULL);
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
