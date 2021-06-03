/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:54:01 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/04 00:38:43 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_state(t_philo *p)
{
	return (p->state);
}

static void	all_is_over(t_info *info)
{
	t_philo	*p;
	int		i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		p = &info->philos[i];
		p->state = STATE_OVER;
	}
}

void		*monitor(void *arg)
{
	t_info	*info;
	int		i;
	int		state;

	info = arg;
	while (!(state & STATE_DEAD) && !(state == STATE_OVER))
	{
		state = 0;
		pthread_mutex_lock(&info->checker);
		i = -1;
		while (!state && ++i < info->num_of_philo)
			state |= check_state(&info->philos[i]);
		pthread_mutex_unlock(&info->checker);
	}
	pthread_mutex_lock(&info->checker);
	all_is_over(info);
	pthread_mutex_unlock(&info->checker);
	return (0);
}
