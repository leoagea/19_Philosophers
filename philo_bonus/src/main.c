/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:24 by lagea             #+#    #+#             */
/*   Updated: 2024/08/15 16:36:40 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_death(t_philo *philo, u_int64_t time)
{
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(1);
	pthread_mutex_lock(&philo->lock);
	if (time - philo->last_eat >= philo->data->death_time)
	{
		philo->status = 1;
		sem_wait(philo->data->write);
		time = get_time() - philo->data->start_time;
		death(philo, time);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac < 5 || ac > 6)
		return (printf("%s\n", ERR_NB_ARG), 1);
	if (check_input(av))
		return (1);
	if (init(&data, av, ac))
		return (1);
	if (loop_process(&data))
		return (1);
	sem_unlink("fork");
	sem_unlink("write");
	return (0);
}
