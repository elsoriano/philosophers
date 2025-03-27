/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/27 18:27:38 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_forensics(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->philos[i].last_meal + data->ttd < ft_timestamp() && \
					data->philos[i].eating == 0)
		{
			data->dead = 1;
			printf("%ld %d died\n", ft_timestamp(), i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_waitress(t_data *data, int j)
{
	while (j < data->n_philo && data->philos[j].finished == 1)
		j++;
	if (j == data->n_philo)
	{
		printf("All Philosophers Eat %d Times\n", data->n_meals);
	}
	return (j);
}

void	ft_checks(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock((&data->lock));
		i = ft_waitress(data, i);
		if (i >= data->n_meals && data->n_meals > 0)
		{
			pthread_mutex_unlock((&data->lock));
			break ;
		}
		if (ft_forensics(data))
		{
			pthread_mutex_unlock((&data->lock));
			break ;
		}
		pthread_mutex_unlock((&data->lock));
		ft_usleep(10);
		i = 0;
	}
	return ;
}

int	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&(data->threads[i]), NULL, \
			ft_routine, &(data->philos[i])))
		{
			printf("Error in pthread_create\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_init(&data, argc, argv))
		return (1);
	if (data.n_philo == 1)
	{
		if (usleep(data.ttd))
			printf("Error in usleep\n");
		printf("%ld 1 Died\n", ft_timestamp());
		return (0);
	}
	else
	{
		if (ft_init_threads(&data))
			return (1);
	}
	ft_checks(&data);
	ft_join_threads(&data);
	ft_free(&data);
	return (0);
}
