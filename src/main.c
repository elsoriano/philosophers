/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/17 12:01:55 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int64_t	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
	}
	ft_free(&data);
	return (0);
}
