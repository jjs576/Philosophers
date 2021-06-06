/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:33:41 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/06 15:56:07 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_info *info)
{
	free(info->philos);
	sem_close(info->forks);
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
