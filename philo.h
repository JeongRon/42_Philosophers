/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:58:38 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/29 21:45:33 by jeongrol         ###   ########.fr       */
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
	int				die_flag;
	pthread_mutex_t	*fork;
}	t_info;

typedef struct s_philo
{
	int			id;
	int			start_time;
	int			cost_time;
	int			fork_left;
	int			fork_right;
	int			eat_cnt;
	t_info		*info;
	pthread_t	thread;	
}	t_philo;

// utils.c
int	ft_strlen(const char *s);
int	ft_error(char *str);
// input_parsing.c
int	input_parsing(int ac, char **av, t_info *info);

#endif 