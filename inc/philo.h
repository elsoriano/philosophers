/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:00:22 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/09 20:35:11 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "libft/inc/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_philo
{
	int	id;
}		t_philo;

typedef struct s_data
{
	int			n_philo;
	uint64_t	ttd;
	uint64_t	tte;
	uint64_t	tts;
	int			n_meals;
}		t_data;

#endif