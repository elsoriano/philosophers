/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:32:12 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/27 14:29:15 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->lock));
	if (!philo->data->dead)
	{
		printf("%ld %d is sleeping\n", ft_timestamp(), philo->id);
		pthread_mutex_unlock(&(philo->data->lock));
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->lock));
		return ;
	}
	ft_usleep(philo->data->tts);
	pthread_mutex_lock(&(philo->data->lock));
	if (!philo->data->dead)
	{
		printf("%ld %d is thinking\n", ft_timestamp(), philo->id);
		pthread_mutex_unlock(&(philo->data->lock));
	}
	else
		pthread_mutex_unlock(&(philo->data->lock));
	return ;
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_lock(&(philo->data->lock));
	if (!philo->data->dead)
	{
		philo->last_meal = ft_timestamp();
		printf("%ld %d has taken a fork\n", ft_timestamp(), philo->id);
		printf("%ld %d has taken a fork\n", ft_timestamp(), philo->id);
		printf("%ld %d is eating\n", ft_timestamp(), philo->id);
		philo->eating = 1;
	}
	pthread_mutex_unlock(&(philo->data->lock));
	ft_usleep(philo->data->tte);
	philo->eating = 0;
	philo->eat_count += 1;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return ;
}

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	pthread_mutex_lock(&(philo->data->lock));
	while (!philo->data->dead)
	{
		pthread_mutex_unlock(&(philo->data->lock));
		ft_eat(philo);
		if (philo->eat_count == philo->data->n_meals && !philo->data->dead)
		{
			pthread_mutex_lock(&(philo->data->lock));
			philo->finished = 1;
			printf("%ld %d finished\n", ft_timestamp(), philo->id);
			pthread_mutex_unlock(&(philo->data->lock));
			return (NULL);
		}
		ft_sleep(philo);
		pthread_mutex_lock(&(philo->data->lock));
	}
	pthread_mutex_unlock(&(philo->data->lock));
	return (NULL);
}
