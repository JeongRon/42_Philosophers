/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:46:04 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/31 07:06:02 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo(t_philo **philo, t_info *info)
{
	int	i;

	(*philo) = (t_philo *)malloc(sizeof(t_philo) * info->philo_cnt);
	if (!(*philo))
		return (ft_error("[Malloc] Philo Error\n"));
	i = -1;
	while (++i < info->philo_cnt)
	{
		(*philo)[i].id = i;
		(*philo)[i].first_time = 0;
		(*philo)[i].start_time = 0;
		(*philo)[i].fork_left = i;
		(*philo)[i].fork_right = (i + 1) % info->philo_cnt;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].option_finish = 0;
		(*philo)[i].info = info;
	}
	return (1);
}
