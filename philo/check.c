/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:34:13 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/08/31 03:20:08 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_argv(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i != argc)
	{
		if (check_is_num(argv[i]))
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (1);
	if (ft_atoi(argv[2]) < 0)
		return (1);
	if (ft_atoi(argv[3]) < 0)
		return (1);
	if (ft_atoi(argv[4]) < 0)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0)
			return (1);
	return (0);
}
