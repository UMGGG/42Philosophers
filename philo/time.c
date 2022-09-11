/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:05:43 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/11 20:31:08 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_get_time(void)
{
	long long		sec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (sec);
}

void	ft_wait(t_param *param, int time)
{
	long long	now_time;
	long long	start_time;

	start_time = ft_get_time();
	while (param->is_all_safe)
	{
		now_time = ft_get_time();
		if (now_time - start_time >= time)
			break ;
		usleep(300);
	}
}
