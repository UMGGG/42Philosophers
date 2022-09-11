/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:20:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/11 21:06:18 by jaeyjeon         ###   ########.fr       */
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
		ft_wait(param, param->time_to_eat);
	if (param->philo_num == 1)
	{
		pthread_mutex_lock(&param->forks[0]);
		ft_print(param, phil, "has taken a fork");
		ft_wait(param, param->time_to_die);
		pthread_mutex_unlock(&param->forks[0]);
		return (0);
	}
	while (param->is_all_safe)
	{
		while (get_fork1(phil, param))
			usleep(100);
		do_sleep(phil, param);
		do_think(phil, param);
		usleep(500);
	}
	return (0);
}

int	get_fork1(t_philo *p, t_param *param)
{
	if (param->is_all_safe == 0)
		return (0);
	pthread_mutex_lock(&param->search_fork);
	if (param->fork_st[p->leftfork] == 0 && param->fork_st[p->rightfork] == 0)
	{
		pthread_mutex_lock(&param->forks[p->leftfork]);
		ft_print(param, p, "has taken a fork");
		param->fork_st[p->leftfork] = 1;
		pthread_mutex_lock(&param->forks[p->rightfork]);
		ft_print(param, p, "has taken a fork");
		param->fork_st[p->rightfork] = 1;
		do_eat(p, param);
		pthread_mutex_unlock(&param->search_fork);
		ft_wait(param, param->time_to_eat);
		param->fork_st[p->leftfork] = 0;
		param->fork_st[p->rightfork] = 0;
		pthread_mutex_unlock(&param->forks[p->leftfork]);
		pthread_mutex_unlock(&param->forks[p->rightfork]);
		p->eat_count++;
		return (0);
	}
	pthread_mutex_unlock(&param->search_fork);
	return (1);
}

void	do_think(t_philo *philo, t_param *param)
{
	if (param->is_all_safe == 0)
		param->is_all_safe = 0;
	else
	{
		ft_print(param, philo, "is thinking");
	}
}

void	do_sleep(t_philo *philo, t_param *param)
{
	if (param->is_all_safe == 0)
		param->is_all_safe = 0;
	else
	{
		ft_print(param, philo, "is sleeping");
		ft_wait(param, param->time_to_sleep);
	}
}

void	do_eat(t_philo *philo, t_param *param)
{
	long long	time;

	if (param->is_all_safe == 0)
		time = 0;
	else
	{
		pthread_mutex_lock(&(param->eat));
		time = ft_get_time() - param->start_time;
		philo->last_eat_time = time;
		ft_print(param, philo, "is eating");
		pthread_mutex_unlock(&(param->eat));
	}
}
