/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/14 00:32:33 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void process_kill(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		kill(data->pid[i], SIGINT);
		i++;	
	}
}

void	monitor(void *philo_pointer)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	while(!philo->status && philo->eat_cont != philo->data->meals_nb)
	{
		eat(philo);
		print(SLEEPING, philo);
		ft_usleep(philo->data->sleep_time);
		print(THINKING, philo);
	}
}

void	*supervisor(void *philo_pointer)
{
	u_int64_t time;
	t_philo *philo;
	
	philo = (t_philo *)philo_pointer;
	while (1)
	{
		time = get_time();
		philo->status = 1;
		if (philo->eat_cont == philo->data->meals_nb)
			return (NULL);
		if (time - philo->last_eat >= philo->data->death_time)
		{
			print(DEAD, philo);
			process_kill(philo->data);
			delete_sema(philo->data);
			free(philo->data->pid);
			exit(1);
		}
	}
	return (NULL);
}

void	routine(void *philo_pointer, int i)
{
	t_philo *philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->death_time;
	philo->eat_cont = 0;
	philo->eating = 0;
	philo->id = i + 1;
	philo->status = 0;
	philo->last_eat = get_time();
	pthread_create(&philo->t1, NULL, &supervisor, &philo);
	monitor(&philo);
	pthread_detach(philo->t1);
}


int	loop_process(t_data *data)
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
		waitpid(data->pid[i], 0, 0);
		i++;
	}
	process_kill(data);
	delete_sema(data);
	return (0);
}
