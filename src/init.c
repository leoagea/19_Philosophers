/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:24:51 by lagea             #+#    #+#             */
/*   Updated: 2024/08/07 18:08:48 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int check_string(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        if (!ft_isdigit((int) str[i]))
            return (1);
    return 0;
}

static void assign_arguments(t_data *data, int i, int nb)
{
    if (i == 1)
        data->nb_philo = nb;
    else if (i == 2)
        data->t_to_die = nb;
    else if (i == 3)
        data->t_to_eat = nb;
    else if (i == 4)
        data->t_to_sleep = nb;
    else if (i == 5)
        data->nb_must_eat = nb;
}

int parse_arg(t_data *data, char **av)
{
    int i;
    int nb;
    (void) data;
    
    i = 1;
    data->nb_must_eat = -1;
    while(av[i])
    {
        if(check_string(av[i]))
            return (printf("Error: Wrong arguments, expected only digits\n"), 1);
        nb = ft_atoi(av[i]);
        if ((nb <= 0 || nb > INT_MAX) && i != 5)
            return (printf("Error: Wrong arguments, expected only positive numbers and less than INT MAX\n"), 1);
        else if ((nb < 0 || nb > INT_MAX) && i == 5)
            return (printf("Error: Wrong last argument, expected positive numbers or 0 and less than INT MAX\n"), 1);
        assign_arguments(data, i, nb);
        i++;
    }
    return 0;
}

int init_philo(t_data *data)
{
    int i;

    i = 0;
    data->philos = malloc(sizeof(t_philo) * data->nb_philo);
    if (!data->philos)
        return 1;
    pthread_mutex_init(&data->dead, NULL);
    pthread_mutex_lock(&data->dead);
    // (*(data->dead)) = 0;
    pthread_mutex_unlock(&data->dead);
    while (i < data->nb_philo)
    {
        data->philos[i].id = i;
        data->philos[i].meals_eaten = 0;
        pthread_mutex_init(&data->philos[i].eat, NULL);
        pthread_mutex_init(&data->philos[i].think, NULL);
        pthread_mutex_init(&data->philos[i].sleep, NULL);
        pthread_mutex_init(&data->philos[i].print, NULL);
        i++;
    }
    return 0;
}
