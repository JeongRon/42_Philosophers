/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:58:38 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/31 07:17:52 by jeongrol         ###   ########.fr       */
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
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
}	t_info;

typedef struct s_philo
{
	int			id;
	time_t		first_time;
	time_t		start_time;
	int			fork_left;
	int			fork_right;
	int			eat_cnt;
	int			option_finish;
	t_info		*info;
	pthread_t	thread;	
}	t_philo;

// utils.c
int	ft_strlen(const char *s);
int	ft_error(char *str);
// input_parsing.c
int	input_parsing(int ac, char **av, t_info *info);
// set_philo.c
int	set_philo(t_philo **philo, t_info info);
// simulate.c
int	simulate(t_info *info, t_philo *philo);
void	*run_thread(void *arg);
void	philo_finish_check(t_info *info, t_philo *philo);

// act_philo.c
int	take_fork(t_philo *philo);
int	eating(t_philo *philo);
int	sleeping(t_philo *philo);
int	thinking(t_philo *philo);
// main.c 
int	print_condition(t_philo *philo, char *str);
time_t	get_time(void);

#endif 