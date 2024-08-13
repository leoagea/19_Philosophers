/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/13 17:19:08 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor(void *data_pointer)
{
	
}

void	*supervisor(void *philo_pointer)
{
	
}

void	*routine(void *philo_pointer, int i)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->death_time;
	philo->eat_cont = 0;
	philo->eating = 0;
	philo->id = i + 1;
	philo->status = 0;
	if (philo->data->philo_num == 1)
	{
		print(FORK, philo);
		ft_usleep(philo->time_to_die);
	}
	while (philo->data->dead != 0)
	{
		
	}
}

int	loop_thread(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			routine(&data->philos[i], i);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		kill(data->pid[i], SIGINT);
		i++;	
	}
	return (0);
}
