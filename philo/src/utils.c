/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:22:07 by rhernand          #+#    #+#             */
<<<<<<< HEAD:src/utils.c
/*   Updated: 2025/03/27 20:08:17 by rhernand         ###   ########.fr       */
=======
/*   Updated: 2025/03/30 16:52:53 by rhernand         ###   ########.fr       */
>>>>>>> exit:philo/src/utils.c
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*Converts string str to int. Returns converted int*/

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	n;

	sign = 1;
	n = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n * sign);
}

void	ft_usleep(uint64_t ms, t_data *data)
{
	uint64_t	start;

	start = ft_timestamp(data);
	while (start + ms > ft_timestamp(data))
		usleep(1000);
}

uint64_t	ft_timestamp(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
<<<<<<< HEAD:src/utils.c
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
=======
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->start);
}
>>>>>>> exit:philo/src/utils.c
