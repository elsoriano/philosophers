/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:32:12 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/27 19:28:11 by rhernand         ###   ########.fr       */
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
	pthread_mutex_lock(&(philo->data->lock));
	philo->eating = 0;
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return ;
}

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->lock));
		if (philo->data->dead)
			return (pthread_mutex_unlock(&(philo->data->lock)), NULL);
		pthread_mutex_unlock(&(philo->data->lock));
		ft_eat(philo);
		pthread_mutex_lock(&(philo->data->lock));
		if (philo->eat_count == philo->data->n_meals && !philo->data->dead)
		{
			philo->finished = 1;
			printf("%ld %d finished\n", ft_timestamp(), philo->id);
			pthread_mutex_unlock(&(philo->data->lock));
			return (NULL);
		}
		else
			pthread_mutex_unlock(&(philo->data->lock));
		ft_sleep(philo);
	}
	return (NULL);
}
