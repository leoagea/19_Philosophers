/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:59:51 by lagea             #+#    #+#             */
/*   Updated: 2025/01/14 13:11:33 by lagea            ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->death_lock);
	if (ft_strcmp(DEAD, str) == 0 && philo->data->dead == 0)
	{
		#ifdef __APPLE__
			printf("[%llu] [%d] " RED "%s" RESET "\n", time, philo->id, str);
		#elif __linux__
			printf("[%lu] [%d] " RED "%s" RESET "\n", time, philo->id, str);
		#endif
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
	{
		#ifdef __APPLE__
			printf("[%llu] [%d] " BLUE "%s" RESET "\n", time, philo->id, str);
		#elif __linux__
			printf("[%lu] [%d] " BLUE "%s" RESET "\n", time, philo->id, str);
		#endif
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->write);
}
