/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:55:35 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/21 21:49:21 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->threads[i], NULL))
		{
			printf("Error Joining Threads");
			ft_free(data);
			exit(1);
		}
		i++;
	}
	return ;
}

void	ft_free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&(data->lock));
}

void	ft_free(t_data *data)
{
	free(data->threads);
	free(data->philos);
	ft_free_forks(data);
}
