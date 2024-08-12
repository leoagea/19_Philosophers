/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:59:51 by lagea             #+#    #+#             */
/*   Updated: 2024/08/12 16:12:03 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ft_error(ERR_GTOD, NULL));
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DEAD, str) == 0 && philo->data->dead == 0)
	{
		printf("[%llu] [%d] " RED "%s" RESET "\n", time, philo->id, str);
		pthread_mutex_lock(&philo->data->death_lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->death_lock);
	}
	if (!philo->data->dead)
		printf("[%llu] [%d] " BLUE "%s" RESET "\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}
