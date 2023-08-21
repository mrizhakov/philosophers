/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:53:52 by mrizakov          #+#    #+#             */
/*   Updated: 2023/08/19 22:37:45 by mrizakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_forks
{
	int				status;
	pthread_mutex_t	mutex;
}	t_forks;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				alone;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		start;
	uint64_t		current;
	uint64_t		death_after_eating;
	t_forks			*fork_left;
	t_forks			*fork_right;
	pthread_t		*thread;
	int				meals;
	int				hungry;
	int				dead;
	int				meal_target;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	uint64_t		start;
	uint64_t		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_target_data;
	int				death;
	int				n_philos_finished;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	death_time_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	time_mutex;
	t_philo			**philo;
	t_forks			**forks;
}	t_data;

int			main(int argc, char **argv);
int			ft_atoi(char *str);
uint64_t	ft_atoi_uint64t(char *str);
int			ft_input_check(char **argv, int argc, t_data *data);
void		ft_mutex_init(t_data *data);
void		ft_create_forks(t_data *v);
void		ft_create_philos(t_data *v);
void		ft_philo_init(t_data *data, int i);
void		ft_thread_init(t_data *data);
void		*ft_routine(void *philo);
int			ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_monitor(t_data *data);
int			ft_die_verify(t_philo *philo, uint64_t start);
void		ft_die_verify_ext(t_philo *philo);
void		will_he_wakeup(t_philo *philo, int status);
uint64_t	get_start_time(void);
uint64_t	get_time(t_philo *philo);
int			print_out(t_philo *philo, char *msg);
void		print_message(void);
int			print_out_expected_death(t_philo *philo, char *msg);
void		ft_free_all(t_data *data);
void		ft_join_philos(t_data *data);
void		ft_destroy_mutex(t_data *data);
void		ft_free_forks(t_data *data);
void		ft_free_philo(t_data *data);
int			ft_int_error_check(char *str);
void		ft_usleep(t_philo *philo, unsigned long long duration);
int			error_no_digit(const char *str);
void		ft_input_convert(char **argv, t_data *data);

#endif //PHILOS_H