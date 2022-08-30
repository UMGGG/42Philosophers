/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:21:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/08/31 04:03:12 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_param	param;

	printf("%d\n", argc);
	if (argc != 5 && argc != 6)
		return (ft_error("[Error]check num of arg"));
	if (ft_philo_init(argc, argv, &param))
		return (1);
	if (ft_start_philo(&param, (&param)->philo))
		return (1);
	return (0);
}
