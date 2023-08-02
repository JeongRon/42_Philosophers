/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:25:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/31 08:12:55 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->fork_left]));
	if (print_condition(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	pthread_mutex_lock(&(philo->info->fork[philo->fork_right]));
	if (print_condition(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	time_t	cost_time;

	if (print_condition(philo, "is eating") == 0)
	{
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	philo->start_time = get_time();
	philo->eat_cnt += 1;
	cost_time = 0;
	while (philo->info->eat_time > cost_time)
		cost_time = get_time() - philo->start_time;
	pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
	pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
	return (1);
}

int	sleeping(t_philo *philo)
{
	time_t		sleep_start_time;
	time_t		cost_time;

	if (print_condition(philo, "is sleeping") == 0)
		return (0);
	sleep_start_time = get_time();
	cost_time = 0;
	while (philo->info->sleep_time > cost_time)
		cost_time = get_time() - sleep_start_time;
	return (1);
}

int	thinking(t_philo *philo)
{
	if (print_condition(philo, "is thinking") == 0)
		return (0);
	return (1);
}
