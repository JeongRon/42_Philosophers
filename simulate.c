/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:48:51 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/14 22:07:15 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	died_check(t_philo *philo)
{
	time_t	philo_life_time;
	int		i;

	i = -1;
	while (++i < philo->info->philo_cnt)
	{
		pthread_mutex_lock(&(philo->info->start));
		philo_life_time = get_time(philo) - philo[i].start_time;
		pthread_mutex_unlock(&(philo->info->start));
		if (philo_life_time > philo->info->life_time)
		{
			print_condition(philo, "died");
			return (0);
		}
	}
	return (1);
}

static int	eat_cnt_check(t_philo *philo)
{
	int		i;

	if (philo->info->option_cnt == -1)
		return (1);
	i = -1;
	while (++i < philo->info->philo_cnt)
	{
		pthread_mutex_lock(&(philo->info->eat));
		if (philo[i].option_finish == 0 && \
			philo[i].eat_cnt == philo->info->option_cnt)
		{
			philo[i].option_finish = 1;
			philo->info->option_finish_cnt++;
		}
		if (philo->info->option_finish_cnt == philo->info->philo_cnt)
		{
			print_condition(philo, "cnt_died");
			pthread_mutex_unlock(&(philo->info->eat));
			return (0);
		}
		pthread_mutex_unlock(&(philo->info->eat));
	}
	return (1);
}

static void	*run_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->info->start));
	pthread_mutex_unlock(&(philo->info->start));
	if (philo->id % 2 == 0)
		thread_sleep(philo->info->eat_time, philo);
	while (1)
	{
		if (take_left_fork(philo) == 0)
			break ;
		if (take_right_fork(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (sleeping_thinking(philo) == 0)
			break ;
	}
	return (NULL);
}

void	simulate(t_philo *philo)
{
	int			i;

	i = -1;
	pthread_mutex_lock(&(philo->info->start));
	while (++i < philo->info->philo_cnt)
	{
		if (pthread_create(&philo[i].thread, NULL, run_thread, &philo[i]))
			return (ft_error("[Thread] Creat Error\n"));
	}
	i = -1;
	philo->info->first_time = get_time(philo);
	while (++i < philo->info->philo_cnt)
		philo[i].start_time = get_time(philo);
	pthread_mutex_unlock(&(philo->info->start));
	while (1)
	{
		if (eat_cnt_check(philo) == 0)
			break ;
		if (died_check(philo) == 0)
			break ;
	}
	i = -1;
	while (++i < philo->info->philo_cnt)
		pthread_join(philo[i].thread, NULL);
}
