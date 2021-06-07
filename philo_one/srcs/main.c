/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:33:41 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 18:23:24 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		print_message(t_philo *p, char *state)
{
	pthread_mutex_lock(p->checker);
	if (!(*p->dying_message))
		printf("%lums %d%s", get_time() - p->start_time, p->index, state);
	if (*p->is_dead)
		*p->dying_message = 1;
	pthread_mutex_unlock(p->checker);
}

static void	free_all(t_info *info)
{
	free(info->philos);
	free(info->forks);
	free(info->tid);
}


static void	get_who_die(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		if (info->is_dead && info->first_die == -1)
		{
			info->first_die = i;
			break ;
		}
	}
}

static void	run(t_info *info)
{
	int	i;
	int	run;

	run = 1;
	while (run)
	{
		pthread_mutex_lock(&info->checker);
		if (info->amount == info->num_of_philo)
			run = 0;
		get_who_die(info);
		pthread_mutex_unlock(&info->checker);
		if (info->first_die != -1)
			run = 0;
	}
	if (info->first_die != -1)
		print_message(&info->philos[info->first_die], MESSAGE_DIE);
	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(info->tid[i], NULL);
}


int			main(int argc, char *argv[])
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (printf("error: bad arguments\n") & 0);
	init(&info, argc, argv);
	run(&info);
	free_all(&info);
	return (0);
}
