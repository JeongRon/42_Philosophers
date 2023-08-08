/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:13:52 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/07 21:00:47 by jeongrol         ###   ########.fr       */
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

time_t	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	print_condition(t_philo *philo, char *str)
{
	time_t	now;
	time_t	print_time;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->finish_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->print));
		return (0);
	}
	now = get_time();
	print_time = now - philo->info->first_time;
	printf("%ld %d %s\n", print_time, philo->id + 1, str);
	if (str[0] == 'd')
		philo->info->finish_flag = 1;
	pthread_mutex_unlock(&philo->info->print);
	return (1);
}
