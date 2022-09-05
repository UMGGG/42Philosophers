/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:21:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/05 16:45:34 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_start_philo(t_param *par, t_philo *philo)
{
	int		i;
	void	*philo_v;

	i = 0;
	par->start_time = ft_get_time();
	while (i < par->philo_num)
	{
		philo_v = (void *)&(philo[i]);
		if (pthread_create(&(philo[i].tid), NULL, do_philo, philo_v) == -1)
			return (ft_error("[Error]thread create fail"));
		i++;
	}
	usleep(par->time_to_die * 1000);
	ft_check_die(par);
	return (0);
}

void	ft_check_die(t_param *par)
{
	int	i;

	i = 0;
	while (par->is_all_safe)
	{
		while (i < par->philo_num)
		{
			pthread_mutex_lock(&(par->eat));
			if (check_eat_time(par, i))
				break ;
			if (check_eat_num(par))
				break ;
			pthread_mutex_unlock(&(par->eat));
			i++;
			usleep(1000);
		}
		i = 0;
	}
	finish_thread(par);
}

int	check_eat_time(t_param *p, int i)
{
	long long	time;

	time = ft_get_time() - p->start_time;
	if ((time - p->philo[i].last_eat_time) > p->time_to_die)
	{
		p->is_all_safe = 0;
		pthread_mutex_lock(&p->print);
		printf("%lldms	%d	is died\n", time, p->philo[i].philo_id);
		return (1);
	}
	return (0);
}

int	check_eat_num(t_param *p)
{
	long long	time;
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (i < p->philo_num)
	{
		if (p->philo[i].eat_count >= p->must_eat_num && p->must_eat_num != -1)
			check++;
		if (check == p->philo_num)
		{
			pthread_mutex_lock(&p->print);
			time = ft_get_time() - p->start_time;
			printf("%lldms	all philo eat %d time\n", time, p->must_eat_num);
			p->is_all_safe = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

void	finish_thread(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->philo_num)
	{
		pthread_detach(param->philo[i].tid);
		i++;
	}
	i = 0;
	while (i < param->philo_num)
	{
		pthread_mutex_destroy(&(param->forks[i]));
		i++;
	}
	free(param->forks);
	free(param->philo);
	free(param->fork_st);
	pthread_mutex_unlock(&param->print);
	pthread_mutex_destroy(&(param->print));
	pthread_mutex_destroy(&(param->eat));
	pthread_mutex_destroy(&(param->search_fork));
}
