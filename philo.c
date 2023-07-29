/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:05:53 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/29 22:17:01 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo(t_philo *philo, t_info info)
{
	int	i;

	philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_cnt);
	if (!philo)
		return (ft_error("[Malloc] Philo Error\n"));
	i = -1;
	while (++i < info.philo_cnt)
	{
		philo[i].id = i;
		philo[i].start_time = 0;
		philo[i].cost_time = 0;
		philo[i].fork_left = 0;
		philo[i].fork_right = 0;
		philo[i].eat_cnt = 0;
		philo[i].info = &info;
	}
	return (1);
}

time_t	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	*run_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_time();
	usleep(100);
	while (1)
	{
		
	}
}

int	simulate(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->philo_cnt)
	{
		philo[i].cost_time = 0; // time 구하기
		if (pthread_create(&(philo[i].thread), NULL, run_thread, &(philo[i])))
			return (ft_rerror("[Thread] Creat Error\n"));
	}
	i = -1;
	while (++i < info->philo_cnt)
		pthread_join(philo[i].thread, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	if (input_parsing(ac, av, &info) == 1)
	{
		if (set_philo(&philo, info) == 1)
		{
			simulate(&info, philo);
		}
	}
	return (0);
}
