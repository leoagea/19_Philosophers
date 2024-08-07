/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:59:51 by lagea             #+#    #+#             */
/*   Updated: 2024/08/07 18:02:39 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void exit(t_data *data)
{
    int i;

    i = 0;
    while (data->philos[i])
    {
        pthread_mutex_destroy(&data->philos[i].eat);
        pthread_mutex_destroy(&data->philos[i].sleep);
        pthread_mutex_destroy(&data->philos[i].think);
        pthread_mutex_destroy(&data->philos[i].dead);
        free(data->philos[i]);
        i++;
    }
}