/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:20:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/02 03:10:25 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*do_philo(void *philo)
{
	t_philo	*phil;
	t_param	*param;

	phil = (t_philo *)philo;
	param = phil->param;
	if (phil->philo_id % 2 != 1)
		usleep(10000);
	while (param->is_all_safe)
	{
		get_fork1(philo, param);
		do_sleep(philo, param);
		do_think(philo, param);
		usleep(100);
	}
	return (0);
}

void	get_fork1(t_philo *philo, t_param *param)
{
	pthread_mutex_lock(&param->forks[philo->leftfork]);
	ft_print(param, philo, "has taken a fork");
	pthread_mutex_lock(&param->forks[philo->rightfork]);
	ft_print(param, philo, "has taken a fork");
	do_eat(philo, param);
	ft_wait(param, param->time_to_eat);
	pthread_mutex_unlock(&param->forks[philo->leftfork]);
	pthread_mutex_unlock(&param->forks[philo->rightfork]);
}

void	do_think(t_philo *philo, t_param *param)
{
	ft_print(param, philo, "is thinking");
}

void	do_sleep(t_philo *philo, t_param *param)
{
	ft_print(param, philo, "is sleeping");
	ft_wait(param, param->time_to_sleep);
}

void	do_eat(t_philo *philo, t_param *param)
{
	long long	time;

	pthread_mutex_lock(&(param->eat[0]));
	philo->eat_count++;
	time = ft_get_time() - param->start_time;
	philo->last_eat_time = time;
	ft_print(param, philo, "is eating");
	pthread_mutex_unlock(&(param->eat[0]));
}
