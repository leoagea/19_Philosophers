/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:26 by lagea             #+#    #+#             */
/*   Updated: 2024/08/07 17:36:37 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static void	skip_whitespace_and_sign(const char **str, int *sign)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;
	long	overflow;

	res = 0;
	sign = 1;
	overflow = 0;
	skip_whitespace_and_sign(&str, &sign);
	while (ft_isdigit(*str))
	{
		res *= 10;
		res += (*str - 48);
		str++;
		if (overflow > res && sign == 1)
			return (-1);
		else if (overflow > res && sign == -1)
			return (-1);
		overflow = res;
	}
	return ((int)res * sign);
}

static long	get_elapsed_time_microseconds(struct timeval start,
		struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec
			- start.tv_usec));
}

void	precise_usleep(long usec)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			rem;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	elapsed = get_elapsed_time_microseconds(start, current);
	rem = usec - elapsed;
	if (rem > 1000)
		usleep(rem / 2);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}
