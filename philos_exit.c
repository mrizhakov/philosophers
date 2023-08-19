/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:19 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/19 21:42:20 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_free_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		free (data->philo[i]->thread);
		free (data->philo[i]);
		i++;
	}
	free (data->philo);
}

void	ft_free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		free (data->forks[i]);
		i++;
	}
	free (data->forks);
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philo)
		{
			if (pthread_mutex_destroy(&(data->forks[i]->mutex)) != 0)
				write(2, "Mutex Destroy fail\n", 19);
			i++;
		}
	}
	if (pthread_mutex_destroy(&(data->dead_mutex)) != 0)
		write(2, "Mutex Destroy fail\n", 19);
	if (pthread_mutex_destroy(&(data->death_time_mutex)) != 0)
		write(2, "Mutex Destroy fail\n", 19);
	if (pthread_mutex_destroy(&(data->meal_mutex)) != 0)
		write(2, "Mutex Destroy fail\n", 19);
	if (pthread_mutex_destroy(&(data->print_mutex)) != 0)
		write(2, "Mutex Destroy fail\n", 19);
	if (pthread_mutex_destroy(&(data->time_mutex)) != 0)
		write(2, "Mutex Destroy fail\n", 19);
	return ;
}

void	ft_free_all(t_data *data)
{
	ft_destroy_mutex(data);
	if (data->philo)
		ft_free_philo(data);
	if (data->forks)
		ft_free_forks(data);
	free (data);
	return ;
}

void	ft_join_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		while (i < data->num_philo && data->philo[i])
		{
			if (pthread_join(*(data)->philo[i]->thread, NULL) != 0)
				write(2, "pthread join fail", 17);
			i++;
		}
	}
	return ;
}
