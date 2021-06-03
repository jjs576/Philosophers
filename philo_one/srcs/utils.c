/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:57:42 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/04 00:10:06 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				ft_atoi(char *s)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	if (!s)
		return (0);
	while (s[++i])
		ret = (ret * 10) + (s[i] - '0');
	return (ret);
}

size_t			get_time(size_t start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000.0 + time.tv_usec / 1000.0 - start_time);
}


void			print_message(t_philo *philo, char *state)
{
	printf("%lums %d%s", get_time(philo->start_time), philo->index, state);
}
