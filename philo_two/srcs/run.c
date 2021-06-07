/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:54:01 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 13:21:56 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_philos_state(t_info *info)
{
	int	state;
	int	i;

	i = -1;
	state = 0;
	while (++i < info->num_of_philo)
	{
		state |= info->philos[i].state;
	}
	return (state);
}

void	set_philos_over(t_info *info)
{
	int		i;
	t_philo	*temp;

	i = -1;
	while (++i < info->num_of_philo)
	{
		temp = &info->philos[i];
		temp->state = STATE_OVER;
	}
}

void	run(t_info *info)
{
	int	state;
	int	i;

	while (1)
	{
		state = get_philos_state(info);
		if (state & STATE_DEAD)
			set_philos_over(info);
		if (state == STATE_OVER || state == STATE_DEAD)
			break ;
	}
	i = -1;
	while (++i < info->num_of_philo)
		pthread_join(info->tid[i], NULL);
}
