/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:33:41 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 22:02:02 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		print_message(t_philo *p, char *state)
{
	if (!(*p->dying_message))
		printf("%lums %d%s", get_time() - p->start_time, p->index, state);
	if (*p->is_dead)
		*p->dying_message = 1;
}

static void	free_all(t_info *info)
{
	free(info->philos);
	sem_close(info->forks);
}

static void	get_who_die(t_info *info)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	while (++i < info->num_of_philo)
	{
		waitpid(info->philos[i].pid, &status, WNOHANG);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) & STATE_DEAD && info->first_die == -1)
			{
				info->first_die = i;
				info->is_dead = 1;
			}
			if (WEXITSTATUS(status) == STATE_OVER)
				info->amount += 1;
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
		if (info->amount == info->num_of_philo)
			run = 0;
		get_who_die(info);
		if (info->first_die != -1)
			run = 0;
	}
	if (info->first_die != -1)
		print_message(&info->philos[info->first_die], MESSAGE_DIE);
	i = -1;
	while (++i < info->num_of_philo)
		kill(info->philos[i].pid, SIGKILL);
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
