/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:24 by lagea             #+#    #+#             */
/*   Updated: 2024/08/14 00:32:59 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static int	case_one(t_data *data)
// {
// 	data->start_time = get_time();
// 	if (pthread_create(&data->philos[0].t1, NULL, &routine, &data->philos[0]))
// 		return (ft_error(ERR_THREAD, data));
// 	pthread_detach(data->philos[0].t1);
// 	while (1)
// 	{
//     	if (data->dead)
//     	{
//     	    break;
//     	}
// 		ft_usleep(0);
// 	}
// 	ft_exit(data);
// 	sem_unlink("fork");
// 	sem_unlink("write");
// 	return (0);
// }

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
	// if (data.philo_num == 1)
		// return (case_one(&data));
	if (loop_process(&data))
		return (1);
	sem_unlink("fork");
	sem_unlink("write");
	return (0);
}
