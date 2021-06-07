/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 22:54:01 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 13:23:41 by jjoo             ###   ########.fr       */
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
		waitpid(info->philos[i].pid, &info->philos[i].status, WNOHANG);
		if (WIFEXITED(info->philos[i].status))
			state |= WEXITSTATUS(info->philos[i].status);
	}
	return (state);
}

void	set_philos_kill(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->num_of_philo)
		kill(info->philos[i].pid, SIGKILL);
}

void	run(t_info *info)
{
	int	state;
	int	i;

	while (1)
	{
		state = get_philos_state(info);
		if (state & STATE_DEAD)
			set_philos_kill(info);
		if (state == STATE_OVER || state == STATE_DEAD)
			break ;
	}
	i = -1;
	while (++i < info->num_of_philo)
		waitpid(info->philos[i].pid, NULL, 0);
}
