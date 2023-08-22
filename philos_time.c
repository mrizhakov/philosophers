/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:48 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/22 21:46:52 by mrizakov         ###   ########.fr       */
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

// uint64_t	ft_get_expected_time_of_death(t_philo *philo)
// {
// 	uint64_t	death_time;

// 	death_time = 0;
// 	pthread_mutex_lock(&philo->data->death_time_mutex);
// 	death_time = philo->death_after_eating;
// 	pthread_mutex_unlock(&philo->data->death_time_mutex);
// 	return (death_time);
// }


// void	ft_dth_flag(t_philo *philo, uint64_t death_time, uint64_t cur_time)
// {
// 	pthread_mutex_lock(&philo->data->dead_mutex);
// 	pthread_mutex_lock(&philo->data->print_mutex);
// 	philo->data->death = 1;
// 	philo->dead = 1;
// 	//if (philo->data->n_philos_finished == philo->data->num_philo)
// 		//usleep(10000);
// 	if ((cur_time - philo->start) > death_time || philo->alone == 1)
// 		printf("%lu %d %s\n", cur_time - philo->start, philo->id, "died");
// 	pthread_mutex_unlock(&philo->data->print_mutex);
// 	pthread_mutex_unlock(&philo->data->dead_mutex);
// 	return ;
// }

// void	ft_exit_after_dinner(t_philo *philo, uint64_t death_time, uint64_t cur_time)
// {
// 	ft_usleep(philo, philo->t_eat);
// 	ft_dth_flag(philo, death_time, cur_time);
// 	return ;
// }

// int	ft_die_verify(t_philo *philo, uint64_t start)
// {
// 	uint64_t	cur_time;
// 	uint64_t	death_time;

// 	cur_time = (get_time(philo));
// 	death_time = ft_get_expected_time_of_death(philo);
// 	pthread_mutex_lock(&philo->data->meal_mutex);
// 	if (philo->data->n_philos_finished == philo->data->num_philo)
// 	{
// 		pthread_mutex_unlock(&philo->data->meal_mutex);
// 		ft_exit_after_dinner(philo, death_time, cur_time);
// 		return (1);
// 	}
// 	else if ((cur_time - start) > death_time || philo->alone == 1)
// 	{
// 		pthread_mutex_unlock(&philo->data->meal_mutex);
// 		ft_dth_flag(philo, death_time, cur_time);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->meal_mutex);
// 	return (0);
// }

// void	ft_monitor(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	usleep(data->time_to_die * 1000);
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->num_philo)
// 		{
// 			if (ft_die_verify(data->philo[i], data->start) == 0)
// 				i++;
// 			else
// 				return ;
// 		}
// 	}
// }

// void	ft_exit_after_dinner(t_philo *philo, uint64_t death_time, uint64_t cur_time);
// void	ft_dth_flag(t_philo *philo, uint64_t death_time, uint64_t cur_time);