/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:48:51 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/08 18:30:23 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulate_finish_check(t_philo *philo)
{
	time_t	philo_life_time;
	int		i;

	i = 0;
	while (philo->info->finish_flag != 1)
	{
		if (philo->info->option_cnt > 0)
		{
			if (philo[i].option_finish == 0 && \
			philo[i].eat_cnt == philo->info->option_cnt)
			{
				philo[i].option_finish = 1;
				philo->info->option_finish_cnt++;
			}
			if (philo->info->option_finish_cnt == philo->info->philo_cnt)
				philo->info->finish_flag = 1;
		}
		philo_life_time = get_time() - philo[i].start_time;
		if (philo_life_time > philo->info->life_time)
			print_condition(philo, "died");
		i = (i + 1) % philo->info->philo_cnt;
	}
}

void	thread_sleep(time_t time)
{
	time_t	begin;

	begin = get_time();
	while (1)
	{
		if (get_time() - begin >= time)
			break ;
		usleep(1000);
	}
}

static void	*run_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->info->start));
	pthread_mutex_unlock(&(philo->info->start));
	if (philo->id % 2 == 0)
		thread_sleep(philo->info->eat_time);
	while (1)
	{
		if (take_fork(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	return (NULL);
}

int	simulate(t_philo *philo)
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
	philo->info->first_time = get_time();
	while (++i < philo->info->philo_cnt)
		philo[i].start_time = get_time();
	pthread_mutex_unlock(&(philo->info->start));
	simulate_finish_check(philo);
	i = -1;
	while (++i < philo->info->philo_cnt)
		pthread_join(philo[i].thread, NULL);
	return (1);
}
