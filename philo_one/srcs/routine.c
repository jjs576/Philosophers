/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:05:20 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/04 00:27:46 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		philo_is_dead(t_philo *philo)
{
	if (philo->last_eat >= philo->time_to_die)
		return (1);
	return(0);
}

static void		philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_message(philo, MESSAGE_FORK);
	pthread_mutex_lock(philo->fork_right);
	print_message(philo, MESSAGE_FORK);
	print_message(philo, MESSAGE_EAT);
	usleep(philo->time_to_eat);
	philo->eat_count++;
	philo->last_eat = get_time(philo->start_time);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void		philo_sleep(t_philo *philo)
{
	print_message(philo, MESSAGE_SLEEP);
	usleep(philo->time_to_sleep);
}

static void		philo_think(t_philo *philo)
{
	print_message(philo, MESSAGE_THINK);
}

void			*routine(void *arg)
{
	t_philo	*p;
	int		is_dead;

	p = arg;
	is_dead = 0;
	while (p->state != STATE_OVER && p->num_of_must_eat != p->eat_count)
	{
		if ((is_dead = philo_is_dead(p)))
			break ;
		philo_eat(p);
		if ((is_dead = philo_is_dead(p)))
			break ;
		philo_sleep(p);
		if ((is_dead = philo_is_dead(p)))
			break ;
		philo_think(p);
	}
	printf("%d end\n", p->index);
	pthread_mutex_lock(p->checker);
	if (is_dead)
		p->state = STATE_DEAD;
	else
		p->state = STATE_OVER;
	pthread_mutex_unlock(p->checker);
	return (0);
}
