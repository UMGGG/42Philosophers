/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:35:37 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/08/31 05:47:55 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_philo_init(int argc, char *argv[], t_param *par)
{
	if (check_argv(argc, argv))
		return (ft_error("[Error]check argv data"));
	par->philo_num = ft_atoi(argv[1]);
	par->time_to_die = ft_atoi(argv[2]);
	par->time_to_eat = ft_atoi(argv[3]);
	par->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		par->must_eat_num = ft_atoi(argv[5]);
	else
		par->must_eat_num = -1;
	par->is_all_safe = 1;
	if (ft_make_philo(par))
		return (ft_error("[Error]malloc philo fail"));
	if (ft_make_forks(par))
		return (1);
	return (0);
}

int	ft_make_philo(t_param *par)
{
	int		i;

	i = 0;
	par->philo = malloc(sizeof(t_param) * (par->philo_num));
	if (par->philo == NULL)
		return (1);
	while (i < par->philo_num)
	{
		par->philo[i].eat_count = 0;
		par->philo[i].last_eat_time = 0;
		par->philo[i].leftfork = i;
		par->philo[i].rightfork = i + 1;
		par->philo[i].param = par;
		par->philo[i].philo_id = i + 1;
		if (i != 0 && i + 1 == par->philo_num)
			par->philo[i].rightfork = 0;
		i++;
	}
	return (0);
}

int	ft_make_forks(t_param *param)
{
	int	i;

	i = 0;
	param->print = malloc(sizeof(pthread_mutex_t));
	if (param->print == NULL)
		return (ft_error("[Error]malloc print fail"));
	if (pthread_mutex_init(&param->print[0], NULL))
		return (ft_error("[Error]print mutex init fail"));
	param->forks = malloc(sizeof(pthread_mutex_t) * (param->philo_num));
	if (param->forks == NULL)
		return (ft_error("[Error]malloc forks fail"));
	while (i < param->philo_num)
	{
		if (pthread_mutex_init(&param->forks[i], NULL))
			return (ft_error("[Error]forks mutex init fail"));
		i++;
	}
	return (0);
}
