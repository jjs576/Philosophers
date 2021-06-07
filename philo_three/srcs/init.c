/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:34:39 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 21:49:27 by jjoo             ###   ########.fr       */
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

static void	init_sema(t_info *info)
{
	sem_unlink("forks");
	info->forks = sem_open("forks", O_CREAT, 0644, info->num_of_philo / 2);
	if (info->forks == SEM_FAILED)
		exit(-1);
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
		temp->start_time = info->start_time;
		temp->last_eat = info->start_time;
		temp->time_to_die = info->time_to_die;
		temp->time_to_eat = info->time_to_eat;
		temp->time_to_sleep = info->time_to_sleep;
		temp->num_of_must_eat = info->num_of_must_eat;
		temp->eat_count = 0;
		temp->forks = info->forks;
		temp->dying_message = &info->dying_message;
		temp->is_dead = &info->is_dead;
	}
}

void		init(t_info *info, int argc, char *argv[])
{
	int		i;
	t_philo	*temp;

	parse_arg(info, argc, argv);
	info->start_time = get_time();
	init_sema(info);
	init_philos(info);
	info->amount = 0;
	info->first_die = -1;
	info->dying_message = 0;
	info->is_dead = 0;
	i = -1;
	while (++i < info->num_of_philo)
	{
		temp = &info->philos[i];
		temp->pid = fork();
		if (temp->pid == 0)
		{
			routine(temp);
		}
	}
}
