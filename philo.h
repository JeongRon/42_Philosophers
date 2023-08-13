/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:58:38 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/13 18:31:07 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int				philo_cnt;
	int				life_time;
	int				eat_time;
	int				sleep_time;
	int				option_cnt;
	int				option_finish_cnt;
	int				finish_flag;
	time_t			first_time;
	int				*fork_state;
	pthread_mutex_t	*fork;
	pthread_mutex_t	start;
	pthread_mutex_t	print;	
	pthread_mutex_t	time;
	pthread_mutex_t	eat;
}	t_info;

typedef struct s_philo
{
	int			id;
	time_t		start_time;
	int			fork_left;
	int			fork_right;
	int			eat_cnt;
	int			option_finish;
	t_info		*info;
	pthread_t	thread;	
}	t_philo;

// set_info.c
int		set_info(int ac, char **av, t_info *info);
// set_philo.c
int		set_philo(t_philo **philo, t_info *info);
// simulate.c
void	thread_sleep(time_t time, t_philo *philo);
int		simulate(t_philo *philo);
// simulate_action.c
int		take_left_fork(t_philo *philo);
int		take_right_fork(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping_thinking(t_philo *philo);
// utils.c
int		ft_strlen(const char *s);
int		ft_error(char *str);
time_t	get_time(t_philo *philo);
int		print_condition(t_philo *philo, char *str);

#endif 