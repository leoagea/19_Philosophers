/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:45:47 by lagea             #+#    #+#             */
/*   Updated: 2024/08/13 14:39:17 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->fork);
	print(FORK, philo);
	sem_wait(philo->data->fork);
	print(FORK, philo);
}

void	drop_forks(t_philo *philo)
{
	sem_post(&philo->data->fork);
	sem_post(&philo->data->fork);
	print(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	// pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	print(EATING, philo);
	philo->eat_cont++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	// pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
