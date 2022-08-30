/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:20:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/08/31 04:23:06 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*do_philo(void *philo)
{
	t_philo	*phil;
	t_param	*param;
	int		i;

	i = 0;
	phil = (t_philo *)philo;
	param = phil->param;
	if (phil->philo_id % 2 == 1)
		usleep(400 * 1000);
	while (param->is_all_safe)
	{
		do_eat(philo, param);
		usleep(param->time_to_eat * 1000);
		do_think(philo, param);
		usleep(1000 * 1000);
		do_sleep(philo, param);
		usleep(param->time_to_sleep * 1000);
		i++;
		if (i == 10)
			param->is_all_safe = 0;
	}
	return (NULL);
}

void	do_think(t_philo *philo, t_param *param)
{
	long long	time;

	time = ft_get_time() - param->start_time;
	printf("%lldms	%d	is thinking\n", time, philo->philo_id);
}

void	do_sleep(t_philo *philo, t_param *param)
{
	long long	time;

	time = ft_get_time() - param->start_time;
	printf("%lldms	%d	is sleeping\n", time, philo->philo_id);
}

void	do_eat(t_philo *philo, t_param *param)
{
	long long	time;

	time = ft_get_time() - param->start_time;
	printf("%lldms	%d	is eating\n", time, philo->philo_id);
}
