/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:24:51 by lagea             #+#    #+#             */
/*   Updated: 2024/08/13 13:46:58 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int init_philo(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (ft_error(ERR_ALLOC_3, data), 1);
	return (0);
}

static int	init_data(t_data *data, char **av, int ac)
{
	data->philo_num = ft_atoi(av[1]);
	data->death_time = (u_int64_t)ft_atoi(av[2]);
	data->eat_time = (u_int64_t)ft_atoi(av[3]);
	data->sleep_time = (u_int64_t)ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0)
		return (ft_error(ERR_2, NULL), 1);
	data->dead = 0;
	data->finished = 0;
	data->fork = sem_open("fork", O_CREAT, 0700, data->philo_num);
	if (data->fork == SEM_FAILED);
		return (ft_error(ERR_SEMA_1, data), 1);
	data->write = sem_open("write", O_CREAT, 0700, 1);
	if (data->write == SEM_FAILED);
		return (ft_error(ERR_SEMA_1, data), 1);
	return (0);
}

int	init(t_data *data, char **av, int ac)
{
	if (init_data(data, av, ac))
		return (1);
	if (init_philo(data))
		return (1);
	return (0);
}
