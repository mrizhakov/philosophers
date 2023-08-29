/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:48 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/23 18:40:36 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_thread_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo && data->death != 1)
	{
		if (data->num_philo == 1)
			data->philo[i]->alone = 1;
		data->philo[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		{
			if (pthread_create(data->philo[i]->thread, 
					NULL, &ft_routine, (void *)data->philo[i]) != 0)
				write(2, "Thread creation fail", 20);
			i++;
		}
	}
	ft_monitor(data);
	ft_join_philos(data);
	return ;
}

void	ft_philo_init(t_data *data, int i)
{
	data->philo[i] = (t_philo *)malloc(sizeof(t_philo));
	if (!data->philo[i])
		ft_free_all(data);
	data->philo[i]->start = data->start;
	data->philo[i]->t_die = data->time_to_die;
	data->philo[i]->t_eat = data->time_to_eat;
	data->philo[i]->t_sleep = data->time_to_sleep;
	data->philo[i]->death_after_eating = 0;
	data->philo[i]->id = i + 1;
	data->philo[i]->dead = 0;
	data->philo[i]->meals = 0;
	data->philo[i]->alone = 0;
	data->philo[i]->meal_target = data->meal_target_data;
	data->philo[i]->data = data;
	if (i == 0)
		data->philo[i]->fork_left = data->forks[data->num_philo - 1];
	else
		data->philo[i]->fork_left = data->forks[i - 1];
	data->philo[i]->fork_right = data->forks[i];
	return ;
}

void	ft_create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo **)malloc((data->num_philo + 1) * sizeof(t_philo *));
	if (!data->philo)
		ft_free_all(data);
	while (i < data->num_philo)
	{
		ft_philo_init(data, i);
		i++;
	}
	data->philo[i] = NULL;
	return ;
}

void	ft_create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (t_forks **)malloc((data->num_philo + 1) * sizeof(t_forks *));
	if (!data->forks)
		ft_free_all(data);
	while (i < data->num_philo)
	{
		data->forks[i] = (t_forks *)malloc(sizeof(t_forks));
		if (pthread_mutex_init(&(data->forks[i])->mutex, NULL) != 0)
		{
			write(2, "Mutex creation fail", 20);
		}
		i++;
	}
	data->forks[i] = NULL;
	return ;
}

void	ft_mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		write(2, "Mutex creation fail", 20);
	if (pthread_mutex_init(&data->death_time_mutex, NULL) != 0)
		write(2, "Mutex creation fail", 20);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		write(2, "Mutex creation fail", 20);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		write(2, "Mutex creation fail", 20);
	if (pthread_mutex_init(&data->time_mutex, NULL) != 0)
		write(2, "Mutex creation fail", 20);
}
