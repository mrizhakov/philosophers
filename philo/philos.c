/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:48 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/22 20:45:05 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ft_input_check(argv, argc, data) == 1)
		return (1);
	ft_input_convert(argv, data);
	ft_mutex_init(data);
	ft_create_forks(data);
	ft_create_philos(data);
	ft_thread_init(data);
	ft_free_all(data);
	return (0);
}
