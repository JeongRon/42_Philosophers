/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:25:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/15 14:53:18 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->fork_left]));
	if (philo->info->fork_state[philo->fork_left] == 0)
		philo->info->fork_state[philo->fork_left] = 1;
	if (print_condition(philo, "has taken a fork") == 0)
	{
		philo->info->fork_state[philo->fork_left] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	return (1);
}

int	take_right_fork(t_philo *philo)
{
	if (philo->info->philo_cnt == 1)
		return (0);
	pthread_mutex_lock(&(philo->info->fork[philo->fork_right]));
	if (philo->info->fork_state[philo->fork_right] == 0)
		philo->info->fork_state[philo->fork_right] = 1;
	if (print_condition(philo, "has taken a fork") == 0)
	{
		philo->info->fork_state[philo->fork_right] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
		philo->info->fork_state[philo->fork_left] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->start));
	philo->start_time = get_time(philo);
	pthread_mutex_unlock(&(philo->info->start));
	if (print_condition(philo, "is eating") == 0)
	{
		philo->info->fork_state[philo->fork_right] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
		philo->info->fork_state[philo->fork_left] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	pthread_mutex_lock(&(philo->info->eat));
	philo->eat_cnt += 1;
	pthread_mutex_unlock(&(philo->info->eat));
	thread_sleep(philo->info->eat_time, philo);
	return (1);
}

int	sleeping_thinking(t_philo *philo)
{
	if (print_condition(philo, "is sleeping") == 0)
	{
		philo->info->fork_state[philo->fork_right] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
		philo->info->fork_state[philo->fork_left] = 0;
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	philo->info->fork_state[philo->fork_right] = 0;
	pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
	philo->info->fork_state[philo->fork_left] = 0;
	pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
	thread_sleep(philo->info->sleep_time, philo);
	if (print_condition(philo, "is thinking") == 0)
		return (0);
	return (1);
}
