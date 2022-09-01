/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:21:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/01 18:11:47 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ls(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_param	param;

	if (argc != 5 && argc != 6)
		return (ft_error("[Error]check num of arg"));
	if (ft_philo_init(argc, argv, &param))
		return (1);
	if (ft_start_philo(&param, (&param)->philo))
		return (1);
	return (0);
}
