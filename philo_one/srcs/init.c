/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:34:39 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 17:57:28 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_arg(t_info *info, int argc, char *argv[])
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
	else
		info->num_of_must_eat = -1;
}

static void	init_mutex(t_info *info)
{
	int	i;

	i = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	while (++i < info->num_of_philo)
		pthread_mutex_init(&(info->forks[i]), NULL);
	pthread_mutex_init(&info->checker, NULL);
}

static void	init_philos(t_info *info)
{
	t_philo	*temp;
	int		i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->num_of_philo);
	while (++i < info->num_of_philo)
	{
		temp = &info->philos[i];
		temp->index = i + 1;
		temp->state = STATE_EAT;
		temp->is_end = &info->amount;
		temp->is_dead = &info->is_dead;
		temp->start_time = info->start_time;
		temp->last_eat = info->start_time;
		temp->time_to_die = info->time_to_die;
		temp->time_to_eat = info->time_to_eat;
		temp->time_to_sleep = info->time_to_sleep;
		temp->num_of_must_eat = info->num_of_must_eat;
		temp->eat_count = 0;
		temp->fork_left = &info->forks[i % info->num_of_philo];
		temp->fork_right = &info->forks[(i + 1) % info->num_of_philo];
		temp->checker = &info->checker;
		temp->dying_message = &info->dying_message;
	}
}

void		init(t_info *info, int argc, char *argv[])
{
	int	i;

	parse_arg(info, argc, argv);
	info->start_time = get_time();
	info->first_die = -1;
	info->is_dead = FALSE;
	info->amount = 0;
	info->dying_message = 0;
	init_mutex(info);
	init_philos(info);
	info->tid = malloc(sizeof(pthread_t) * info->num_of_philo);
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_create(&info->tid[i], NULL, routine, (void*)&info->philos[i]);
		i += 2;
	}
	i = 1;
	usleep(100);
	while (i < info->num_of_philo)
	{
		pthread_create(&info->tid[i], NULL, routine, (void*)&info->philos[i]);
		i += 2;
	}
}
