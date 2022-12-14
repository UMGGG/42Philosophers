/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:51:17 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/06 19:10:47 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_whitespace(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	pm;

	num = 0;
	pm = 1;
	i = check_whitespace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pm *= -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			num *= 10;
			num += (int)(str[i] - 48);
		}
		else
			break ;
		i++;
	}
	return (pm * num);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	ft_print(t_param *param, t_philo *philo, char *str)
{
	long long	time;

	if (param->is_all_safe == 0)
		time = 0;
	else
	{
		pthread_mutex_lock(&param->print);
		if (param->is_all_safe != 0)
		{
			time = ft_get_time() - param->start_time;
			printf("%lldms	%d	%s\n", time, philo->philo_id, str);
		}
		pthread_mutex_unlock(&param->print);
	}
}
