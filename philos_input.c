/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:48 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/22 20:54:48 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_input_check(char **argv, int argc, t_data *data)
{
	if (argc < 5 || argc > 6 
		|| ft_int_error_check(argv[1]) == 0
		|| ft_int_error_check(argv[2]) == 0
		|| ft_int_error_check(argv[3]) == 0
		|| ft_int_error_check(argv[4]) == 0)
	{
		print_message();
		free(data);
		return (1);
	}
	if (argv[5] && ft_int_error_check(argv[5]) == 0)
	{
		print_message();
		free(data);
		return (1);
	}
	return (0);
}

void	ft_input_convert(char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi_uint64t(argv[2]);
	data->time_to_eat = ft_atoi_uint64t(argv[3]);
	data->time_to_sleep = ft_atoi_uint64t(argv[4]);
	data->start = get_start_time();
	if (argv[5])
		data->meal_target_data = ft_atoi(argv[5]);
	else
		data->meal_target_data = -2;
	data->death = 0;
	data->n_philos_finished = 0;
	return ;
}

void	print_message(void)
{
	printf("Only positive numbers are allowed!\n");
	printf("Usage: philosophers number_of_philosophers\n");
	printf("time_to_die time_to_eat time_to_sleep\n");
	printf("Optional: number_of_times_each_philosopher_must_eat\n");
}

int	error_no_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_int_error_check(char *str)
{
	int			i;
	long long	sig;
	long long	res;

	i = 0;
	sig = 1;
	res = 0;
	if (error_no_digit(str) == 1)
		return (0);
	if (str[0] == '-')
		return (0);
	while (str[i])
	{
		res = res + (str[i] - '0');
		if (str[i + 1] != '\0')
			res = res * 10;
		i++;
		if (res == 0 || res >= INT_MAX)
			return (0);
	}
	return (res * sig);
}
