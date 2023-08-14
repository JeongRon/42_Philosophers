/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:13:52 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/14 17:08:53 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

time_t	get_time(t_philo *philo)
{
	struct timeval	current;
	time_t			now_time;

	pthread_mutex_lock(&(philo->info->time));
	gettimeofday(&current, NULL);
	now_time = current.tv_sec * 1000 + current.tv_usec / 1000;
	pthread_mutex_unlock(&(philo->info->time));
	return (now_time);
}

void	thread_sleep(time_t time, t_philo *philo)
{
	time_t	begin;

	begin = get_time(philo);
	while (1)
	{
		if (get_time(philo) - begin >= time)
			break ;
		usleep(1000);
	}
}

int	print_condition(t_philo *philo, char *str)
{
	time_t	now;
	time_t	print_time;

	pthread_mutex_lock(&(philo->info->print));
	if (philo->info->finish_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->print));
		return (0);
	}
	else if (str[0] == 'c')
	{
		philo->info->finish_flag = 1;
		pthread_mutex_unlock(&(philo->info->print));
		return (1);
	}
	else
	{
		now = get_time(philo);
		print_time = now - philo->info->first_time;
		printf("%ld %d %s\n", print_time, philo->id + 1, str);
		if (str[0] == 'd')
			philo->info->finish_flag = 1;
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
}
