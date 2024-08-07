/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:24 by lagea             #+#    #+#             */
/*   Updated: 2024/08/08 00:34:48 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int ac, char **av)
{
    (void) av;
    t_data data;
    
    if (ac != 5 && ac != 6)
        return (printf("Error: Wrong number of arguments, expected 4 or 5\n"), 1);
    if (parse_arg(&data, av))
        return (1);
    printf("nb philo : %d\ntime to die : %d\ntime to eat : %d\ntime to sleep : %d\nnb of times each philo must eat : %d\n", data.nb_philo, data.t_to_die, data.t_to_eat, data.t_to_sleep, data.nb_must_eat);
    if (init_philo(&data)  || init_fork(&data))
        printf("Error Allocation array philos or fork\n");
    ft_exit(&data);
    return 0;   
}
