/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:20:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/08/31 06:30:06 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*do_philo(void *philo)
{
	t_philo	*phil;
	t_param	*param;

	phil = (t_philo *)philo;
	param = phil->param;
	if (phil->philo_id % 2 == 1)
		usleep(param->time_to_eat * 1000);
	while (param->is_all_safe)
	{
		get_fork(philo, param);
		do_sleep(philo, param);
		usleep(param->time_to_sleep * 1000);
		usleep(200);
		do_think(philo, param);
	}
	return (0);
}

void	get_fork(t_philo *philo, t_param *param)
{
	long long	time;

	pthread_mutex_lock(&param->forks[philo->leftfork]);
	time = ft_get_time() - param->start_time;
	pthread_mutex_lock(&param->print[0]);
	printf("%lldms	%d	has taken a fork\n", time, philo->philo_id);
	pthread_mutex_unlock(&param->print[0]);
	pthread_mutex_lock(&param->forks[philo->rightfork]);
	time = ft_get_time() - param->start_time;
	pthread_mutex_lock(&param->print[0]);
	printf("%lldms	%d	has taken a fork\n", time, philo->philo_id);
	pthread_mutex_unlock(&param->print[0]);
	do_eat(philo, param);
	usleep(param->time_to_eat * 1000);
	pthread_mutex_unlock(&param->forks[philo->leftfork]);
	pthread_mutex_unlock(&param->forks[philo->rightfork]);
}

void	do_think(t_philo *philo, t_param *param)
{
	long long	time;

	time = ft_get_time() - param->start_time;
	pthread_mutex_lock(&param->print[0]);
	printf("%lldms	%d	is thinking\n", time, philo->philo_id);
	pthread_mutex_unlock(&param->print[0]);
}

void	do_sleep(t_philo *philo, t_param *param)
{
	long long	time;

	time = ft_get_time() - param->start_time;
	pthread_mutex_lock(&param->print[0]);
	printf("%lldms	%d	is sleeping\n", time, philo->philo_id);
	pthread_mutex_unlock(&param->print[0]);
}

void	do_eat(t_philo *philo, t_param *param)
{
	long long	time;

	time = ft_get_time() - param->start_time;
	philo->last_eat_time = time;
	pthread_mutex_lock(&param->print[0]);
	printf("%lldms	%d	is eating\n", time, philo->philo_id);
	pthread_mutex_unlock(&param->print[0]);
}
