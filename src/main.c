/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/22 22:00:17 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_forensics(t_data *data)
{
	int			i;
	uint64_t	dtime;

	i = 0;
	dtime = 0;
	while (i < data->n_philo)
	{
		if (data->philos[i].last_meal + data->ttd < ft_timestamp() && \
					data->philos[i].eating == 0)
		{
			dtime = ft_timestamp();
			pthread_mutex_lock(&(data->lock));
			printf("%d %d died\n", ft_timestamp(), i + 1);
			pthread_mutex_unlock(&(data->lock));
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
		ft_join_threads(data);
		printf("All Philosophers Eat %d Times\n", data->n_meals);
		ft_free(data);
		exit(0);
	}
	return (j);
}

void	ft_checks(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		while (i < data->n_philo)
		{
			j = ft_waitress(data, j);
			ft_forensics(&(data->philos[i]));
			i++;
		}
		ft_usleep(10);
		i = 0;
	}
}

void	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&(data->threads[i]), NULL, \
			ft_routine, &(data->philos[i])))
		{
			printf("Error in pthread_create\n");
			ft_free(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return ;
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
		ft_free(&data);
		return (0);
	}
	else
		ft_init_threads(&data);
	ft_checks(&data);
	return (0);
}
