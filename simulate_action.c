/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:25:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/08 17:34:24 by jeongrol         ###   ########.fr       */
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
	if (print_condition(philo, "is eating") == 0)
	{
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
		pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
		return (0);
	}
	philo->start_time = get_time();
	philo->eat_cnt += 1;
	thread_sleep(philo->info->eat_time);
	pthread_mutex_unlock(&(philo->info->fork[philo->fork_right]));
	pthread_mutex_unlock(&(philo->info->fork[philo->fork_left]));
	if (philo->info->finish_flag == 1)
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (print_condition(philo, "is sleeping") == 0)
		return (0);
	thread_sleep(philo->info->sleep_time);
	if (philo->info->finish_flag == 1)
		return (0);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (print_condition(philo, "is thinking") == 0)
		return (0);
	if (philo->info->finish_flag == 1)
		return (0);
	return (1);
}

// int *fork;
// pthread_mutex_t	*m_fork;

// 1, 0

// // 뮤텍스는 포크를 변경하거나 조회할때만 사용되어야 합니다.

// while (1) 	
// {
// 	if (left_fork == 1) {
// 		mutex_lock(m_fork);
// 		left_fork = 0;
// 		mutex_unlock(m_fork);
// 	}

// }
