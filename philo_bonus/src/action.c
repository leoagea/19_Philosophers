/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:45:47 by lagea             #+#    #+#             */
/*   Updated: 2024/08/14 17:05:43 by lagea            ###   ########.fr       */
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
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	print(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->last_eat = get_time();
	print(EATING, philo);
	ft_usleep(philo->data->eat_time);
	philo->eat_cont++;
	drop_forks(philo);
}
