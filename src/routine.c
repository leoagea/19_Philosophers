/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/12 01:57:47 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			print(DEAD, philo);
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		print(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	loop_thread(t_data *data)
{
	int			i;
	pthread_t	thread0;

	i = -1;
	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&thread0, NULL, &monitor, &data->philos[0]))
			return (ft_error(ERR_THREAD, data));
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->thread[i], NULL, &routine, &data->philos[i]))
			return (ft_error(ERR_THREAD, data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->thread[i], NULL))
			return (ft_error(ERR_JOIN, data));
	}
	return (0);
}
