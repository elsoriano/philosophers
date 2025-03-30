/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
<<<<<<< HEAD:src/main.c
/*   Updated: 2025/03/27 20:05:16 by rhernand         ###   ########.fr       */
=======
/*   Updated: 2025/03/30 16:54:16 by rhernand         ###   ########.fr       */
>>>>>>> exit:philo/src/main.c
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_forensics(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&(data->lock));
		if (data->philos[i].last_meal + data->ttd < ft_timestamp(data) && \
					data->philos[i].eating == 0)
		{
			data->dead = 1;
			printf("%ld %d died\n", ft_timestamp(data), i + 1);
			pthread_mutex_unlock(&(data->lock));
			return (1);
		}
		pthread_mutex_unlock(&(data->lock));
		i++;
	}
	return (0);
}

int	ft_waitress(t_data *data, int j)
{
	pthread_mutex_lock(&(data->lock));
	while (j < data->n_philo && data->philos[j].finished == 1)
		j++;
	pthread_mutex_unlock(&(data->lock));
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
		i = ft_waitress(data, i);
		if (i >= data->n_philo && data->n_meals > 0)
			return ;
		if (ft_forensics(data))
			return ;
		ft_usleep(10, data);
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

	if (argc < 5 || argc > 6)
		return (printf("Invalid number of Arguments\n"), 1);
	if (1 == ft_atoi(argv[1]))
	{
		usleep((uint64_t) ft_atoi(argv[2]));
		printf("%ld 1 Died\n", ft_timestamp(&data));
		return (0);
	}
	if (ft_init(&data, argc, argv))
		return (1);
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
