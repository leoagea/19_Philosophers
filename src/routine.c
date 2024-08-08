/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/09 00:45:00 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void print(t_data *data, t_philo *philo, int mode)
{
    pthread_mutex_lock(&philo->print);
    if (mode == FORK && !data->dead)
        printf("[%zd] [%d]"BLUE" has taken a fork"RESET"\n", get_current_time(), philo->id);
    else if (mode == EAT && !data->dead)
        printf("[%zd] [%d]"GREEN" is eating"RESET"\n", get_current_time(), philo->id);
    else if (mode == SLEEP && !data->dead)
        printf("[%zd] [%d]"MAGENTA" is sleeping"RESET"\n", get_current_time(), philo->id);
    else if (mode == THINK)
        printf("[%zd] [%d]"CYAN" is thinking"RESET"\n", get_current_time(), philo->id);
    pthread_mutex_unlock(&philo->print);
}

void eat(t_data *data, t_philo *philo)
{
    (void) data;
    // philo->meals_eaten++;
    pthread_mutex_lock(philo->l_fork);
    print(data, philo, FORK);
    if (data->nb_philo == 1)
    {
        precise_usleep(data->t_to_die * 1000);
        data->dead = 1;
        print(data, philo, DEAD);
        pthread_mutex_unlock(philo->l_fork);
        return ;
    }
    pthread_mutex_lock(philo->r_fork);
    print(data, philo, FORK);
    print(data, philo, EAT);
    precise_usleep(data->t_to_eat * 1000);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    philo->last_eat = get_current_time();
}

void *routine(void *p)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)p;
    data = philo->data;
    if (!(philo->id % 2))
        precise_usleep((data->t_to_sleep / 2) * 1000);
    while(data->dead != 1 || data->all_eaten <= data->nb_philo)
    {
        eat(data, philo);
        if (philo->meals_eaten == data->nb_must_eat)
            data->all_eaten++;
        print(data, philo, SLEEP);
        precise_usleep(data->t_to_sleep);
        print(data, philo, THINK);
    }
    return NULL;
}

static void check_death(t_data *data, int i)
{
    if(get_current_time() - data->philos[i].last_eat > (size_t)data->t_to_die)
    {
        pthread_mutex_lock(&data->philos[i].monitoring);
        if(data->dead == 0)
        {
            print(data, &data->philos[i], DEAD);
            data->dead = 1;
        }
        pthread_mutex_unlock(&data->philos[i].monitoring);
        return ;
    }
}

void monitoring(t_data *data)
{
    int i;

    while(data->dead != 1 || data->all_eaten <= data->nb_philo)
    {
        i = -1;
        while(++i < data->nb_philo)
        {
            pthread_mutex_lock(&data->philos[i].eat);
            if (data->all_eaten == data->nb_philo)
            {
                pthread_mutex_lock(&data->philos[i].eat);
                return ;
            }
            check_death(data, i);
            pthread_mutex_unlock(&data->philos[i].eat);
        }
    }
    return ;
}
