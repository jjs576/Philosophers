/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:33:41 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/04 00:20:39 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_for_monitor(t_info *info)
{
	int	ret;

	ret = 0;
	pthread_join(info->tid_monitor, NULL);
	return (ret);
}

static void	free_all(t_info *info)
{
	free(info->philos);
	free(info->forks);
}

int			main(int argc, char *argv[])
{
	t_info	info;
	int		ret;

	ret = 0;
	if (argc != 5 && argc != 6)
		return (printf("error: bad arguments\n") & 0);
	init(&info, argc, argv);
	ret = wait_for_monitor(&info);
	free_all(&info);
	return (ret);
}
