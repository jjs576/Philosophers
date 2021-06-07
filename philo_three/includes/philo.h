/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:00:00 by jjoo              #+#    #+#             */
/*   Updated: 2021/06/07 22:02:21 by jjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>

# define TRUE			1
# define FALSE			0

# define STATE_EAT		0x00000001
# define STATE_SLEEP	0x00000002
# define STATE_THINK	0x00000004
# define STATE_DEAD		0x00000008
# define STATE_OVER		0x00000010

# define MESSAGE_FORK	" has taken a fork\n"
# define MESSAGE_EAT	" is eating\n"
# define MESSAGE_SLEEP	" is sleeping\n"
# define MESSAGE_THINK	" is thinking\n"
# define MESSAGE_DIE	" died\n"

typedef struct	s_philo
{
	size_t			start_time;
	int				state;
	size_t			last_eat;
	int				index;
	int				eat_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_must_eat;
	pid_t			pid;
	sem_t			*forks;
	int				*dying_message;
	int				*is_dead;
}				t_philo;

typedef struct	s_info
{
	size_t			start_time;
	int				first_die;
	int				amount;
	int				num_of_philo;
	int				dying_message;
	int				is_dead;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_must_eat;
	t_philo			*philos;
	sem_t			*forks;
}				t_info;

void			print_message(t_philo *philo, char *state);

void			routine(t_philo *p);

void			init(t_info *info, int argc, char **argv);

int				ft_max(int a, int b);
int				ft_min(int a, int b);
int				ft_atoi(char *s);
size_t			get_time(void);
void			ft_sleep(size_t time);

#endif
