/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:59:51 by lagea             #+#    #+#             */
/*   Updated: 2024/08/08 00:49:17 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_exit(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->philos[i].eat);
        if (&data->fork[i])
			pthread_mutex_destroy(&data->fork[i]);
        i++;
    }
    if (data->fork)
		free(data->fork);
	if (data->philos)
		free(data->philos);
}