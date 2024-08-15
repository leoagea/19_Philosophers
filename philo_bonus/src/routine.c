/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/15 16:35:57 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	process_kill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		kill(data->pid[i], SIGINT);
		i++;
	}
}

void	monitor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->status || philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_unlock(&philo->lock);
			return ;
		}
		pthread_mutex_unlock(&philo->lock);
		eat(philo);
		print(THINKING, philo);
	}
}

void	*supervisor(void *philo_pointer)
{
	u_int64_t	time;
	t_philo		*philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		time = get_time();
		pthread_mutex_lock(&philo->lock);
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_unlock(&philo->lock);
			return (NULL);
		}
		if (time - philo->last_eat >= philo->data->death_time)
		{
			check_death(philo, time);
		}
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(10);
	}
	return (NULL);
}

void	routine(t_data *data, int i)
{
	t_philo	philo;

	philo.data = data;
	philo.eat_cont = 0;
	philo.id = i + 1;
	philo.status = 0;
	if (philo.id % 2 == 0)
		ft_usleep(data->sleep_time / 2);
	philo.last_eat = get_time();
	pthread_mutex_init(&philo.lock, NULL);
	pthread_create(&philo.t1, NULL, &supervisor, &philo);
	monitor(&philo);
	pthread_detach(philo.t1);
}

int	loop_process(t_data *data)
{
	int	i;

	i = 0;
	data->pid = malloc(sizeof(int) * data->philo_num);
	if (!data->pid)
		return (ft_error(ERR_ALLOC_2, data), 1);
	while (i < data->philo_num)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			data->philos[i].data = data;
			routine(data, i);
		}
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
