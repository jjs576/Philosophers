/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:05:20 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 13:22:23 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(t_philo *philo, char *state)
{
	printf("%lums %d%s", get_time() - philo->start_time, philo->index, state);
}

static void	philo_eat(t_philo *p)
{
	sem_wait(p->forks);
	print_message(p, MESSAGE_FORK);
	print_message(p, MESSAGE_FORK);
	print_message(p, MESSAGE_EAT);
	p->last_eat = get_time();
	ft_sleep(ft_min(p->time_to_eat, p->time_to_die));
	p->eat_count++;
	sem_post(p->forks);
	p->state &= ~STATE_EAT;
	p->state |= STATE_SLEEP;
}

static void	philo_sleep(t_philo *p)
{
	size_t	time1;
	size_t	time2;

	print_message(p, MESSAGE_SLEEP);
	time1 = ft_max(p->time_to_eat, p->time_to_sleep);
	time2 = p->time_to_die - p->time_to_eat;
	ft_sleep(ft_min(time1, time2));
	p->state &= ~STATE_SLEEP;
	p->state |= STATE_THINK;
}

static void	philo_think(t_philo *p)
{
	print_message(p, MESSAGE_THINK);
	p->state &= ~STATE_THINK;
	p->state |= STATE_EAT;
}

void		*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	p->state |= STATE_EAT;
	while (p->state & STATE_RUN)
	{
		if (p->eat_count == p->num_of_must_eat)
			p->state = STATE_OVER;
		if (get_time() - p->last_eat >= p->time_to_die)
			p->state = STATE_DEAD;
		if (p->state & STATE_EAT)
			philo_eat(p);
		else if (p->state & STATE_SLEEP)
			philo_sleep(p);
		else if (p->state & STATE_THINK)
			philo_think(p);
	}
	if (p->state == STATE_DEAD)
		print_message(p, MESSAGE_DIE);
	return (0);
}
