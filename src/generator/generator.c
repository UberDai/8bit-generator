/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 04:12:03 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/08 04:41:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wav.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define INCREMENT	(2 * M_PI * (440 + i * 0.005) / 44100)

int	generate_sound(t_wav *file, t_sound *params, short **data)
{
	int		data_size;

	data_size = params->duration * file->bytes_per_frame * file->sample_rate;
	data_size /= file->bytes_per_frame;
	*data = malloc(data_size);

	for (int i = 0; i < data_size; i++)
		(*data)[i] = (short) (SHRT_MAX * sin(INCREMENT * i));

	return (data_size);
}