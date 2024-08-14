/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:59:51 by lagea             #+#    #+#             */
/*   Updated: 2024/08/14 18:04:04 by lagea            ###   ########.fr       */
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

	sem_wait(philo->data->write);
	time = get_time() - philo->data->start_time;
	printf("[%llu] [%d] " BLUE "%s" RESET "\n", time, philo->id, str);
	sem_post(philo->data->write);
}

void	delete_sema(t_data *data)
{
	sem_close(data->fork);
	sem_close(data->write);
	sem_unlink("fork");
	sem_unlink("write");
}

void	death(t_philo *philo, u_int64_t time)
{
	printf("[%llu] [%d] " RED "%s" RESET "\n", time, philo->id, DEAD);
	process_kill(philo->data);
	sem_post(philo->data->write);
	delete_sema(philo->data);
	free(philo->data->pid);
	exit(1);
}
