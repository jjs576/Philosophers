/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:57:42 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 13:23:20 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int				ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

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

size_t			get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000.0 + time.tv_usec / 1000.0);
}

void			ft_sleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}
