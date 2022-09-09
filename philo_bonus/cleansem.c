/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleansem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:34:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/09 17:45:29 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main()
{
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("print");
	sem_unlink("search");
	return (0);
}
